*This project has been created as part of the 42 curriculum by deferrei.*

# Codexion

## Description

Codexion is a multithreaded simulation written in C that models a shared co-working
hub where several **coders**, sitting in a circle, take turns **compiling**, **debugging**,
and **refactoring**. In the center of the hub lies a shared quantum compiler that
requires **two USB dongles** at once to compile: one from each hand, shared with
the coder's left and right neighbours.

Each coder is represented by a dedicated POSIX thread. Coders repeatedly cycle
through compiling, debugging, and refactoring, and must compile again before their
personal `time_to_burnout` deadline elapses, or they **burn out** and the simulation
stops. A separate monitor thread continuously watches every coder's deadline and
detects burnout with millisecond precision.

The project's core challenge is coordinating concurrent access to a small, shared,
circularly-distributed pool of resources (the dongles) without deadlocking, without
starving any coder, and while respecting a configurable arbitration policy (`fifo` or
`edf`) whenever multiple coders compete for the same dongle.

The simulation stops in one of two ways:
- a coder burns out (fails to start compiling within `time_to_burnout` ms of their
  last compile, or of the start of the simulation), or
- every coder has completed at least `number_of_compiles_required` compiles.

## Instructions

### Compilation

```bash
make
```

This builds the `codexion` binary using `cc` with the flags `-Wall -Wextra -Werror
-pthread`.

Other Makefile rules:
```bash
make clean   # remove object files
make fclean  # remove object files and the binary
make re      # fclean + all
```

### Execution

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
           time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

| Argument                    | Meaning                                                                                   |
|------------------------------|---------------------------------------------------------------------------------------------|
| `number_of_coders`           | Number of coders (and number of dongles).                                                   |
| `time_to_burnout` (ms)       | Time since the last compile start (or simulation start) before a coder burns out.           |
| `time_to_compile` (ms)       | Time a coder spends compiling, holding two dongles.                                         |
| `time_to_debug` (ms)         | Time a coder spends debugging.                                                              |
| `time_to_refactor` (ms)      | Time a coder spends refactoring.                                                             |
| `number_of_compiles_required`| Simulation stops successfully once every coder has compiled at least this many times.        |
| `dongle_cooldown` (ms)       | Time a dongle stays unavailable after being released.                                        |
| `scheduler`                  | Arbitration policy for dongle contention: `fifo` or `edf`.                                   |

Example:
```bash
./codexion 5 800 200 200 200 3 100 edf
```

All arguments are mandatory. Invalid input (negative numbers, non-integers, or a
scheduler other than `fifo`/`edf`) is rejected with an error message.

## Blocking cases handled

- **Deadlock prevention (Coffman's conditions).** A coder always requests both of
  its dongles (left and right) as a single atomic step protected by one mutex
  (`mutex_dongle`), rather than acquiring them one at a time. This removes the
  classic "hold and wait" circular-wait pattern (the dining philosophers deadlock):
  no coder can hold one dongle while blocked waiting for the other, since both are
  only ever marked as taken together, inside the same critical section.

- **Starvation prevention.** Coders competing for the same dongle are arbitrated
  using the requested `scheduler` policy (`fifo` or `edf`), evaluated only among the
  coders that are actually waiting on a **shared** dongle. Coders that do not share
  any dongle with one another run fully in parallel and never block each other. Every
  release of a dongle triggers a `pthread_cond_broadcast`, so priority is
  re-evaluated fairly on every opportunity, guaranteeing liveness: under `edf`, no
  waiting coder can be starved indefinitely as long as the parameters are feasible.

- **Cooldown handling.** After a coder releases its two dongles, each dongle is
  timestamped with `cool_down = current_time + dongle_cooldown`. A dongle is only
  considered available again once `get_time() >= cool_down`, which is checked both
  before granting a dongle and inside the condition guarding the wait loop.

- **Precise burnout detection.** A dedicated monitor thread polls every coder's
  deadline (`last_compile_start + time_to_burnout`, or `time_to_burnout` if the
  coder has not compiled yet) at a fine-grained interval (`usleep(1000)`, 1 ms), so
  burnout is detected and logged within the required 10 ms tolerance. A coder
  currently compiling is never flagged, since `is_compiling` is checked under its
  own mutex before evaluating the deadline.

- **Log serialization.** All state-change messages (`has taken a dongle`, `is
  compiling`, `is debugging`, `is refactoring`, `burned out`) go through a single
  `print_save()` function that locks a dedicated `mutex_print` around the `printf`
  call, guaranteeing that two messages from different threads are never interleaved
  on the same line.

- **Clean shutdown without residual blocking.** When the simulation ends
  successfully (every coder reached the required number of compiles, with no
  burnout), the shared `runnig` flag is explicitly set to `false` once all coder
  threads have joined. The monitor thread, which polls this flag, then exits
  cleanly instead of running forever and leaving the program hung on
  `pthread_join`.

## Thread synchronization mechanisms

- **`pthread_mutex_t mutex_dongle`** protects the state of all dongles (`free`,
  `cool_down`) as a whole, as well as the shared wait-list used for scheduling
  arbitration. Acquiring both dongles a coder needs happens under a single lock
  of this mutex, which is what prevents duplicate allocation of a dongle and what
  makes the two-dongle acquisition atomic (see deadlock prevention above).

- **`pthread_mutex_t mutex_state`** protects the shared `runnig` boolean flag,
  which signals whether the simulation is still active. Every thread (coders,
  monitor, main scheduling logic) reads this flag exclusively through a helper
  function, `is_running()`, that copies the value into a local variable under the
  lock before releasing it. This avoids ever reading a partially-updated or
  torn value of a shared variable outside of mutex protection, which would
  otherwise be a data race.

- **`pthread_mutex_t mutex_print`** serializes all `printf` calls used for state
  logging (see log serialization above).

- **`pthread_mutex_t coder->mutex`** (one per coder) protects that coder's own
  fields that are read by both its own thread and the monitor thread concurrently:
  `is_compiling`, `has_compiled`, `last_compile`. Any write to these fields (in
  `compiling()`) and any read of them (in the monitor's `monitoring_flow()`) happen
  under this same per-coder mutex, preventing the monitor from observing an
  inconsistent, half-written state.

- **`pthread_cond_t cond_dongles`** is used inside the dongle-waiting loop
  (`cond_selector()`), combined with `pthread_cond_wait` or `pthread_cond_timedwait`
  (the latter used when a dongle is currently in cooldown, so the waiting coder
  wakes up automatically once the cooldown expires rather than polling). It is
  signalled with `pthread_cond_broadcast` every time a dongle is released, which
  wakes up every coder currently waiting so the scheduler policy (fifo/edf) can be
  re-evaluated fairly among them.

**Example: preventing a race on `is_compiling`.**

Without protection, the coder thread writing `is_compiling = true` and the monitor
thread reading it to decide whether to flag a burnout could interleave unsafely.
Both accesses are wrapped with `pthread_mutex_lock(&coder->mutex)` and
`pthread_mutex_unlock(&coder->mutex)`, so the monitor always sees a fully
committed value, never a stale or torn one. This was confirmed with Helgrind,
which initially reported this exact race and reported zero errors after the fix.

**Example: thread-safe communication between coders and the monitor.**

The monitor never directly signals a coder to stop. Instead, burnout sets the
shared `runnig` flag to `false` under `mutex_state` and broadcasts on
`cond_dongles`, so any coder currently blocked waiting for a dongle wakes up,
re-checks `is_running()`, and exits its loop cleanly, without any direct
thread-to-thread signalling that could otherwise race.

## Resources

- [POSIX Threads Programming (LLNL tutorial)](https://hpc-tutorials.llnl.gov/posix/)
- [Threads tutorial](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
- [Helgrind: a thread error detector (Valgrind manual)](https://valgrind.org/docs/manual/hg-manual.html)
- Liu, C. L. and Layland, J. W., *Scheduling Algorithms for Multiprogramming in a
  Hard-Real-Time Environment* (background reading on the Earliest Deadline First
  scheduling policy)
- [Heap: heap implemetation tutorial](https://www.geeksforgeeks.org/c/heap-in-c/)

**AI usage:** An AI assistant was used throughout development, primarily to
interpret Helgrind/Valgrind output and pinpoint the exact lines responsible for
reported data races and deadlocks, and to review.
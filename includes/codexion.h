#ifndef CODEXION_H
# define CODEXION_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <time.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>

# define CODERS 1
# define TIME_BURNOUT 2
# define TIME_COMPILE 3
# define TIME_DEBUG 4
# define TIME_REFACTOR 5
# define NUMBER_COMPILES 6
# define DONGLE_COOLDOWN 7
# define SCHEDULER 8
# define ERROR -1


typedef struct error_s
{
	char *str;
} error_t;

typedef struct dongle_s
{
	int				id;
	bool			free;
	long			cool_down;
}					dongle_t;

typedef struct program_s program_t;
struct timespec	get_timeout(long timestamp);

typedef	struct coder_s
{
	pthread_t		coder;
	dongle_t		*left;
	dongle_t		*right;
	pthread_cond_t	cond;
	pthread_mutex_t	mutex;
	program_t		*program;

	long		time_to_burnout;
	long		last_compile;
	long		request_order;
	int			id;
	int			compile_times;
	int			dongles;
	bool		burned_out;
	bool		can_run;
	bool		finished;
	bool		has_compiled;
	bool		is_compiling;
}				coder_t;


typedef struct program_s
{
	int				numbers_coders;
	int				numbers_of_compiles;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	long			dongle_cooldown;
	long			start_time;
	long			request_counter;

	pthread_mutex_t	mutex_state;
	pthread_t		monitor;
	coder_t			*coders;
	dongle_t		*dongles;
	pthread_mutex_t	mutex_dongle;
	pthread_cond_t	cond_dongles;
	pthread_mutex_t	mutex_print;

	bool			runnig;
	char			*scheduler;
} 					program_t;

typedef struct heap_s
{
	coder_t			**coders;
	int				size;
	int				capacity;
	char			*scheduler;
	pthread_mutex_t mutex;
}			heap_t;


bool		invalid_numbers(const char *str);
bool		signal(char c);
bool		args_validation(error_t *error, program_t *program);
bool		is_stoping(coder_t **coder);
bool		is_running(program_t *program);




int			parser(const char *numbers_coders, error_t **error);
int			has_priority(coder_t *coder_a, coder_t *coder_b, char *scheduler);
int			scheduler(program_t *program);
int			save_args(char **argv, program_t **program, error_t *error);

long		parser_long(const char *numbers_coders, error_t **error);
long		deadline(coder_t *coder);
long		get_time(void);

void		take_dongle(coder_t **coder);
void		release_dongle(coder_t **coder);
void		compiling(coder_t **coder);
void		debugging(coder_t **coder);
void		refactoring(coder_t **coder);
void		*burnout_monitoring(void *arg);
void		print_save(program_t *pg, char *str, long time, int id);
void		wake_up(program_t **program);
void		flow(coder_t **coder);
void		join_pthread(program_t **program);


program_t	*generator_engine(char **argv, error_t *error);
heap_t		*heap_init(int capacity, char *scheduler, program_t **program);
coder_t		*heappop(heap_t **heap);



void		create_coders(program_t	*program, coder_t *coder, int id);
void		create_dongle(dongle_t *dongle, int id);
void		free_engine(program_t *program);
void		heapfy(heap_t **heap, int i);
void		heappush(heap_t	**heap, coder_t	*coder);
void		swap(coder_t **coder_a, coder_t **coder_b);
void		free_heap(heap_t *heap);
void		*coder_routine(void *arg);
void		program_usage();
void		create_objects(program_t **program);
void		cond_selector(coder_t *coder);

char		*error_message(const char *str);
char		*ft_strcpy(char *src);

#endif
#ifndef CODEXION_H
# define CODEXION_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <time.h>
# include <stdbool.h>

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
	pthread_mutex_t	mutex_dongle;
	int				id;
}					dongle_t;

typedef	struct coder_s
{
	pthread_t	coder;
	dongle_t	*left;
	dongle_t	*right;

	int			id;
	int			last_compile;
	int			time_to_burnout;
	int			dongles;
	bool		burned_out;
}				coder_t;

typedef struct program_s
{
	int				numbers_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				numbers_of_compiles;
	int				dongle_cooldown;

	pthread_mutex_t	mutex_state;
	coder_t			*coders;
	dongle_t		*dongles;

	int				runnig;
	char			*scheduler;
} 					program_t;

typedef struct heap_s
{
	coder_t	**coders;
	int		size;
	int		capacity;
	char	*scheduler;
}			heap_t;


bool		invalid_numbers(const char *str);
bool		signal(char c);
int			parser(const char *numbers_coders, error_t **error);
int			save_args(char **argv, program_t **program, error_t *error);
int			dealine(coder_t *coder);
int		has_priority(coder_t *coder_a, coder_t *coder_b, char *scheduler);



program_t	*generator_engine(char **argv, error_t *error);
coder_t		create_coders(program_t	**program, int id);
dongle_t	create_dongles(int id);
heap_t		*heap_init(int capacity, char *scheduler);
coder_t		*heappop(heap_t **heap,  char *scheduler);

void		*couder_routine(void *);
void		free_engine(program_t *program);
void		heapfy(heap_t **heap, int i, char *scheduler);
void		heappush(heap_t	**heap, coder_t	*coder, char *scheduler);
void		swap(coder_t **coder_a, coder_t **coder_b);
void		free_heap(heap_t *heap);

char		*error_message(const char *str);
char		*ft_strcpy(char *src);


#endif
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
	long		last_compile;
	long		time_to_burnout;
	int			dongles;
	bool		burned_out;
}				coder_t;

typedef struct program_s
{
	int				numbers_coders;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	int				numbers_of_compiles;
	long			dongle_cooldown;

	pthread_mutex_t	mutex_state;
	coder_t			*coders;
	dongle_t		*dongles;

	bool			runnig;
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
bool		args_validation(error_t *error, program_t *program);
int			parser(const char *numbers_coders, error_t **error);
long		parser_long(const char *numbers_coders, error_t **error);
int			save_args(char **argv, program_t **program, error_t *error);
long		deadline(coder_t *coder);
int			has_priority(coder_t *coder_a, coder_t *coder_b, char *scheduler);
long		get_time(void);



program_t	*generator_engine(char **argv, error_t *error);
coder_t		create_coders(program_t	**program, int id);
dongle_t	create_dongles(int id);
heap_t		*heap_init(int capacity, char *scheduler, program_t **program);
coder_t		*heappop(heap_t **heap);

void		free_engine(program_t *program);
void		heapfy(heap_t **heap, int i);
void		heappush(heap_t	**heap, coder_t	*coder);
void		swap(coder_t **coder_a, coder_t **coder_b);
void		free_heap(heap_t *heap);
void		*coder_routine(void *coder);
void		program_usage();


char		*error_message(const char *str);
char		*ft_strcpy(char *src);


#endif
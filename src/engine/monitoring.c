#include "../../includes/codexion.h"

void	*burnout_monitoring(void *arg)
{
	long		now;
	int			i;
	program_t	*program;
	bool		compiling_now;
	long		dead_line;
	bool		running;

	program = (program_t *)arg;
	pthread_mutex_lock(&program->mutex_state);
	running = program->runnig;
	pthread_mutex_unlock(&program->mutex_state);
	while (running)
	{
		i = 0;
		now = get_time() - program->start_time;
		while (i < program->numbers_coders)
		{
			pthread_mutex_lock(&(program->coders[i].mutex));
			compiling_now = program->coders[i].is_compiling;
			dead_line = deadline(&program->coders[i]);
			pthread_mutex_unlock(&(program->coders[i].mutex));
			if (!compiling_now && now >= dead_line)
				{
				pthread_mutex_lock(&program->mutex_state);
				if (!program->coders[i].burned_out)
				{
					program->coders[i].burned_out = true;
					program->runnig = false;
					pthread_mutex_lock(&program->mutex_print);
					printf("%lu %d burned out\n", now, program->coders[i].id);
					pthread_mutex_unlock(&program->mutex_print);
				}
				pthread_mutex_unlock(&program->mutex_state);
				wake_up(&program);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

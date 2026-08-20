#include "../../includes/codexion.h"

void	*burnout_monitoring(void *arg)
{
	long		now;
	int			i;
	program_t	*program;

	program = (program_t *)arg;
	while (program->runnig)
	{
		i = 0;
		now = get_time() - program->start_time;
		while (i < program->numbers_coders)
		{
			if (!program->coders[i].is_compiling
				&& now >= deadline(&program->coders[i]))
				{
				pthread_mutex_lock(&program->mutex_state);
				if (!program->coders[i].burned_out)
				{
					program->coders[i].burned_out = true;
					program->runnig = false;
					printf("%lu %d burned out\n", now, program->coders[i].id);
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

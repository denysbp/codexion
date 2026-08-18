#include "../../includes/codexion.h"

void	*coder_routine(void *arg)
{
	coder_t	*coder;

	coder = (coder_t *)arg;
	pthread_mutex_lock(&coder->mutex);
	while (coder->compile_times)
	{
		while (!coder->can_run)
		{
			pthread_cond_wait(&coder->cond, &coder->mutex);
		}
		printf("Coder %d foi autorizado\n", coder->id);
		coder->can_run = false;
		pthread_mutex_unlock(&coder->mutex);

		pthread_mutex_lock(&coder->mutex);

		take_dongle(&coder);
		coder->finished = true;
		coder->compile_times--;
		pthread_cond_signal(&coder->cond);
		pthread_mutex_unlock(&coder->mutex);
		printf("Coder %d terminou execucao\n", coder->id);
	}
	return (NULL);
}

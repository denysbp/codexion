#include "../../includes/codexion.h"

void	*coder_routine(void *arg)
{
	coder_t	*coder;

	coder = (coder_t *)arg;
	while (coder->compile_times)
	{
		pthread_mutex_lock(&coder->mutex);
		while (!coder->can_run && !is_stoping(&coder))
			pthread_cond_wait(&coder->cond, &coder->mutex);
		coder->can_run = false;
		pthread_mutex_unlock(&coder->mutex);
		if (is_stoping(&coder))
			return (NULL);
		take_dongle(&coder);
		if(is_stoping(&coder))
			return (NULL);
		compiling(&coder);
		if(is_stoping(&coder))
			return (NULL);
		debugging(&coder);
		if(is_stoping(&coder))
			return (NULL);
		refactoring(&coder);
		release_dongle(&coder);
		pthread_mutex_lock(&coder->mutex);
		coder->finished = true;
		coder->compile_times--;
		pthread_cond_signal(&coder->cond);
		pthread_mutex_unlock(&coder->mutex);
	}
	return (NULL);
}

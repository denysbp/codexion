#include "../../includes/codexion.h"


int	scheduler(program_t *program)
{
	heap_t	*heap;
	coder_t	*coder;

	program->start_time = get_time();
	pthread_create(&program->monitor, NULL, &burnout_monitoring, program);
	heap = heap_init(program->numbers_coders, program->scheduler, &program);
	coder = heappop(&heap);
	while (coder && program->runnig)
	{
		pthread_mutex_lock(&coder->mutex);
		coder->can_run = true;
		pthread_cond_signal(&coder->cond);
		pthread_mutex_unlock(&coder->mutex);
		pthread_mutex_lock(&coder->mutex);
		while (!coder->finished)
		{
			pthread_cond_wait(&coder->cond, &coder->mutex);
		}
		coder->finished = false;
		pthread_mutex_unlock(&coder->mutex);
		if (coder->compile_times != 0)
			heappush(&heap, coder);
		coder = heappop(&heap);
	}
	for (int i = 0; i < program->numbers_coders; i++)
	{
		pthread_join(program->coders[i].coder, NULL);
	}
	free_heap(heap);
	return (0);
}

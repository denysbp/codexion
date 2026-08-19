#include "../../includes/codexion.h"



int	take_dongle(coder_t **coder)
{	long	time_stamp;

	time_stamp = get_time() - (*coder)->program->start_time;
	printf("%lu %d  has taken a dongle\n", time_stamp, (*coder)->id);
	pthread_mutex_lock(&(*coder)->program->mutex_dongle);
	while (!(*coder)->right->free || !(*coder)->left->free)
	{
		pthread_cond_wait(&(*coder)->program->cond_dongles, &(*coder)->program->mutex_dongle);
	}
	(*coder)->right->free = false;
	(*coder)->left->free = false;
	(*coder)->dongles = 2;
	pthread_mutex_unlock(&(*coder)->program->mutex_dongle);
	return (1);
}


int	release_dongle(coder_t **coder)
{
	pthread_mutex_lock(&(*coder)->program->mutex_dongle);
	(*coder)->right->free = true;
	(*coder)->left->free = true;
	pthread_cond_broadcast(&(*coder)->program->cond_dongles);
	pthread_mutex_unlock(&(*coder)->program->mutex_dongle);
	// printf("Coder %d realase the dongle\n", (*coder)->id);
	return (1);
}

int	compiling(coder_t **coder)
{
	return (0);
}
#include "../../includes/codexion.h"



int	take_dongle(coder_t **coder)
{
	printf("Coder %d", (*coder)->id);
	pthread_mutex_lock(&(*coder)->program->mutex_dongle);
	while (!(*coder)->right->free || !(*coder)->left->free)
	{
		pthread_cond_wait(&(*coder)->program->cond_dongles, &(*coder)->program->mutex_dongle);
	}
	pthread_mutex_unlock(&(*coder)->program->mutex_dongle);
	pthread_mutex_lock(&(*coder)->program->mutex_dongle);
	(*coder)->right->free = false;
	(*coder)->left->free = false;
	pthread_cond_broadcast(&(*coder)->program->cond_dongles);
	pthread_mutex_unlock(&(*coder)->program->mutex_dongle);
	return (1);
}
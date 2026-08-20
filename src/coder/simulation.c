#include "../../includes/codexion.h"



void	take_dongle(coder_t **coder)
{
	long	time_stamp;
	pthread_mutex_lock(&(*coder)->program->mutex_dongle);

	while (!(*coder)->right->free
		|| !(*coder)->left->free
		|| get_time() < (*coder)->right->cool_down
		|| get_time() < (*coder)->left->cool_down)
	{

	}

	(*coder)->right->free = false;
	(*coder)->left->free = false;
	(*coder)->dongles = 2;

	pthread_mutex_unlock(&(*coder)->program->mutex_dongle);
	time_stamp = get_time() - (*coder)->program->start_time;
	printf("%lu %d has taken a dongle\n", time_stamp, (*coder)->id);
	return ;
}


void	release_dongle(coder_t **coder)
{
	long	cool_down;

	cool_down = get_time() + (*coder)->program->dongle_cooldown;
	pthread_mutex_lock(&(*coder)->program->mutex_dongle);
	(*coder)->right->free = true;
	(*coder)->left->free = true;
	(*coder)->dongles = 0;
	(*coder)->right->cool_down = cool_down;
	(*coder)->left->cool_down = cool_down;
	pthread_cond_broadcast(&(*coder)->program->cond_dongles);
	pthread_mutex_unlock(&(*coder)->program->mutex_dongle);
	return ;
}

void	compiling(coder_t **coder)
{
	long	time_stamp;

	time_stamp = get_time() - (*coder)->program->start_time;
	(*coder)->last_compile = time_stamp;
	printf("%lu %d is compiling\n", time_stamp, (*coder)->id);
	usleep((*coder)->program->time_to_compile * 1000);
	return ;
}

void	debugging(coder_t **coder)
{
	long	time_stamp;

	time_stamp = get_time() - (*coder)->program->start_time;
	printf("%lu %d is debugging\n", time_stamp, (*coder)->id);
	usleep((*coder)->program->time_to_debug * 1000);
	return ;
}

void	refactoring(coder_t **coder)
{
	long	time_stamp;

	time_stamp = get_time() - (*coder)->program->start_time;
	printf("%lu %d is refactoring\n", time_stamp, (*coder)->id);
	usleep((*coder)->program->time_to_refactor * 1000);
	return ;
}
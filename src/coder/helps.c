#include "../../includes/codexion.h"

void	cond_selector(coder_t *coder)
{
	long				now;
	long				next_cooldown;
	struct timespec		timeout;

	now = get_time();
	next_cooldown = 0;
	if (now < coder->right->cool_down)
		next_cooldown = coder->right->cool_down;
	if (now < coder->left->cool_down
		&& (next_cooldown == 0
			|| coder->left->cool_down < next_cooldown))
		next_cooldown = coder->left->cool_down;
	if (next_cooldown > 0)
	{
		timeout = get_timeout(next_cooldown);
		pthread_cond_timedwait(
			&coder->program->cond_dongles,
			&coder->program->mutex_dongle,
			&timeout);
	}
	else
		pthread_cond_wait(
			&coder->program->cond_dongles,
			&coder->program->mutex_dongle);
}

void	wake_up(program_t **program)
{
	int	i;

	i = 0;
	while (i < (*program)->numbers_coders)
	{
		pthread_mutex_lock(&(*program)->coders[i].mutex);
		(*program)->coders[i].finished = true;
		pthread_cond_signal(&(*program)->coders[i].cond);
		pthread_mutex_unlock(&(*program)->coders[i].mutex);
		i++;
	}
	return ;
}


bool	is_stoping(coder_t **coder)
{
	if (!(*coder)->program->runnig)
	{
		release_dongle(coder);
		return (true);
	}
	return (false);
}
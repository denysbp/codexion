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

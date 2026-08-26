/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:14:58 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/26 14:19:58 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	cond_selector(t_coder *coder)
{
	long				now;
	long				next_cooldown;
	struct timespec		timeout;

	now = get_time();
	next_cooldown = 0;
	if (now < coder->right->cool_down)
		next_cooldown = coder->right->cool_down;
	if (now < coder->left->cool_down && (next_cooldown == 0
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

void	wake_up(t_program **program)
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
	pthread_mutex_lock(&(*program)->mutex_dongle);
	pthread_cond_broadcast(&(*program)->cond_dongles);
	pthread_mutex_unlock(&(*program)->mutex_dongle);
	return ;
}

bool	is_stoping(t_coder **coder)
{
	if (!is_running((*coder)->program))
	{
		if ((*coder)->dongles)
			release_dongle(coder);
		return (true);
	}
	return (false);
}

bool	is_running(t_program *program)
{
	bool	running;

	pthread_mutex_lock(&program->mutex_state);
	running = program->runnig;
	pthread_mutex_unlock(&program->mutex_state);
	return (running);
}

bool	has_higher_priority_waiter(t_heap *heap, t_coder *coder)
{
	int	i;

	i = 0;
	while (i < heap->size)
	{
		if (heap->coders[i] != coder
			&& coder_shares_dongle(heap->coders[i], coder)
			&& has_priority(heap->coders[i], coder, heap->scheduler))
			return (true);
		i++;
	}
	return (false);
}

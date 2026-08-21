/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:12 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/21 19:58:38 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

int	scheduler(t_program *program)
{
	t_heap	*heap;
	t_coder	*coder;

	program->start_time = get_time();
	pthread_create(&program->monitor, NULL, &burnout_monitoring, program);
	heap = heap_init(program->numbers_coders, program->scheduler, &program);
	coder = heappop(&heap);
	while (coder && is_running(program))
	{
		flow(&coder);
		if (!program->runnig)
			break ;
		if (coder->compile_times != 0)
			heappush(&heap, coder);
		coder = heappop(&heap);
	}
	pthread_mutex_lock(&program->mutex_state);
	program->runnig = false;
	pthread_mutex_unlock(&program->mutex_state);
	join_pthread(&program);
	free_heap(heap);
	return (0);
}

void	flow(t_coder **coder)
{
	pthread_mutex_lock(&(*coder)->mutex);
	(*coder)->program->request_counter++;
	(*coder)->request_order = (*coder)->program->request_counter++;
	(*coder)->can_run = true;
	pthread_cond_signal(&(*coder)->cond);
	pthread_mutex_unlock(&(*coder)->mutex);
	pthread_mutex_lock(&(*coder)->mutex);
	while (!(*coder)->finished)
	{
		pthread_cond_wait(&(*coder)->cond, &(*coder)->mutex);
	}
	(*coder)->finished = false;
	pthread_mutex_unlock(&(*coder)->mutex);
	return ;
}

void	join_pthread(t_program **program)
{
	int	i;

	i = 0;
	while (i < (*program)->numbers_coders)
	{
		pthread_join((*program)->coders[i].coder, NULL);
		i++;
	}
	pthread_join((*program)->monitor, NULL);
	return ;
}

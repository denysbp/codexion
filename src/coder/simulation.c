/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:04 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/26 13:51:36 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	take_dongle(t_coder **coder)
{
	long		time_stamp;
	t_program	*program;

	program = (*coder)->program;
	pthread_mutex_lock(&program->mutex_dongle);
	(*coder)->request_order = program->request_counter++;
	heappush(&program->wait_heap, *coder);
	while (is_running(program) && is_free(program, coder))
	{
		cond_selector(*coder);
	}
	heap_remove(program->wait_heap, *coder);
	if (!is_running(program))
	{
		pthread_mutex_unlock(&program->mutex_dongle);
		return ;
	}
	(*coder)->right->free = false;
	(*coder)->left->free = false;
	(*coder)->dongles = 2;
	pthread_mutex_unlock(&program->mutex_dongle);
	time_stamp = get_time() - program->start_time;
	print_save(program, "has taken a dongle", time_stamp, (*coder)->id);
	print_save(program, "has taken a dongle", time_stamp, (*coder)->id);
	return ;
}

void	release_dongle(t_coder **coder)
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

void	compiling(t_coder **coder)
{
	long	time_stamp;

	time_stamp = get_time() - (*coder)->program->start_time;
	pthread_mutex_lock(&(*coder)->mutex);
	(*coder)->last_compile = time_stamp;
	(*coder)->has_compiled = true;
	(*coder)->is_compiling = true;
	(*coder)->compile_times--;
	pthread_mutex_unlock(&(*coder)->mutex);
	print_save((*coder)->program, "is compiling", time_stamp, (*coder)->id);
	usleep((*coder)->program->time_to_compile * 1000);
	pthread_mutex_lock(&(*coder)->mutex);
	(*coder)->is_compiling = false;
	pthread_mutex_unlock(&(*coder)->mutex);
	return ;
}

void	debugging(t_coder **coder)
{
	long	time_stamp;

	time_stamp = get_time() - (*coder)->program->start_time;
	print_save((*coder)->program, "is debugging", time_stamp, (*coder)->id);
	usleep((*coder)->program->time_to_debug * 1000);
	return ;
}

void	refactoring(t_coder **coder)
{
	long	time_stamp;

	time_stamp = get_time() - (*coder)->program->start_time;
	print_save((*coder)->program, "is refactoring", time_stamp, (*coder)->id);
	usleep((*coder)->program->time_to_refactor * 1000);
	return ;
}

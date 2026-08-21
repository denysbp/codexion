/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:09 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/21 19:58:10 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	*burnout_monitoring(void *arg)
{
	long		now;
	t_program	*program;
	bool		running;

	program = (t_program *)arg;
	pthread_mutex_lock(&program->mutex_state);
	running = program->runnig;
	pthread_mutex_unlock(&program->mutex_state);
	while (running)
	{
		now = get_time() - program->start_time;
		if (monitoring_flow(&program, now))
			return (NULL);
		pthread_mutex_lock(&program->mutex_state);
		running = program->runnig;
		pthread_mutex_unlock(&program->mutex_state);
		usleep(1000);
	}
	return (NULL);
}

bool	monitoring_flow(t_program **program, long now)
{
	int		i;
	long	compiling_now;
	long	dead_line;

	i = 0;
	while (i < (*program)->numbers_coders)
	{
		pthread_mutex_lock(&((*program)->coders[i].mutex));
		compiling_now = (*program)->coders[i].is_compiling;
		dead_line = deadline(&(*program)->coders[i]);
		pthread_mutex_unlock(&((*program)->coders[i].mutex));
		if (!compiling_now && now >= dead_line)
		{
			burnout(program, &(*program)->coders[i], now);
			return (true);
		}
		i++;
	}
	return (false);
}

void	burnout(t_program **program, t_coder *coder, long now)
{
	pthread_mutex_lock(&(*program)->mutex_state);
	if (!coder->burned_out)
	{
		coder->burned_out = true;
		(*program)->runnig = false;
		print_save((*program), "burned out", now, coder->id);
	}
	pthread_mutex_unlock(&(*program)->mutex_state);
	pthread_mutex_lock(&(*program)->mutex_dongle);
	pthread_cond_broadcast(&(*program)->cond_dongles);
	pthread_mutex_unlock(&(*program)->mutex_dongle);
	wake_up(program);
	return ;
}

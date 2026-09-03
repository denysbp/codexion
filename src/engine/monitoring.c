/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:09 by deferrei          #+#    #+#             */
/*   Updated: 2026/09/03 21:15:55 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	*burnout_monitoring(void *arg)
{
	long		now;
	t_program	*program;

	program = (t_program *)arg;
	while (is_running(program))
	{
		now = get_time() - program->start_time;
		if (monitoring_flow(&program, now))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

bool	monitoring_flow(t_program **program, long now)
{
	int		i;
	long	compiling_now;
	long	dead_line;

	i = 0;
	pthread_mutex_lock(&(*program)->mutex_state);
	dead_line = (*program)->time_to_burnout;
	pthread_mutex_unlock(&(*program)->mutex_state);

	while (i < (*program)->numbers_coders)
	{
		pthread_mutex_lock(&((*program)->coders[i].mutex));
		compiling_now = (*program)->coders[i].is_compiling;
		pthread_mutex_unlock(&((*program)->coders[i].mutex));
		if (!compiling_now && now - (*program)->coders[i].last_compile >= dead_line)
		{
			burnout(program, &(*program)->coders[i]);
			return (true);
		}
		i++;
	}
	return (false);
}

void	burnout(t_program **program, t_coder *coder)
{
	pthread_mutex_lock(&(*program)->mutex_state);
	if (!coder->burned_out)
	{
		coder->burned_out = true;
		(*program)->runnig = false;
		print_save((*program), "burned out", coder->id);
	}
	pthread_mutex_unlock(&(*program)->mutex_state);
	pthread_mutex_lock(&(*program)->mutex_dongle);
	pthread_cond_broadcast(&(*program)->cond_dongles);
	pthread_mutex_unlock(&(*program)->mutex_dongle);
	wake_up(program);
	return ;
}

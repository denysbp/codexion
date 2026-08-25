/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:12 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/25 15:07:59 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

int	scheduler(t_program *program)
{
	pthread_create(&program->monitor, NULL, &burnout_monitoring, program);
	join_pthread(&program);
	return (0);
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
	pthread_mutex_lock(&(*program)->mutex_state);
	(*program)->runnig = false;
	pthread_mutex_unlock(&(*program)->mutex_state);
	pthread_join((*program)->monitor, NULL);
	return ;
}

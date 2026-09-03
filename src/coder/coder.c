/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:14:49 by deferrei          #+#    #+#             */
/*   Updated: 2026/09/03 21:04:18 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	create_coders(t_program	*program, t_coder *coder, int id)
{
	coder->id = id;
	coder->burned_out = false;
	coder->time_to_burnout = program->time_to_burnout;
	coder->dongles = 0;
	coder->last_compile = 0;
	coder->left = &program->dongles[id - 1];
	coder->right = &program->dongles[id % program->numbers_coders];
	coder->can_run = false;
	coder->finished = false;
	coder->compile_times = 0;
	coder->program = program;
	coder->is_compiling = false;
	coder->has_compiled = false;
	coder->request_order = 0;
	pthread_mutex_init(&coder->mutex, NULL);
	pthread_cond_init(&coder->cond, NULL);
}

void	create_dongle(t_dongle *dongle, int id)
{
	dongle->id = id;
	dongle->free = true;
	dongle->cool_down = 0;
}

long	deadline(t_coder *coder)
{
	if (!coder->has_compiled)
	{
		return (coder->time_to_burnout);
	}
	return (coder->last_compile + coder->time_to_burnout);
}

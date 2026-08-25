/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:07 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/25 16:05:09 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

t_program	*generator_engine(char **argv, t_error *error)
{
	t_program	*program;
	int			i;

	i = 0;
	program = malloc(sizeof(t_program));
	if (save_args(argv, &program, error) == ERROR)
		return (free(program), NULL);
	program->coders = malloc(sizeof(t_coder) * program->numbers_coders);
	program->dongles = malloc(sizeof(t_dongle) * program->numbers_coders);
	pthread_mutex_init(&program->mutex_state, NULL);
	pthread_mutex_init(&program->mutex_dongle, NULL);
	pthread_mutex_init(&program->mutex_print, NULL);
	pthread_cond_init(&program->cond_dongles, NULL);
	program->wait_heap = wait_heap_init(program->numbers_coders,
			program->scheduler);
	program->runnig = true;
	program->request_counter = 0;
	create_objects(&program);
	while (i < program->numbers_coders)
	{
		pthread_create(&program->coders[i].coder,
			NULL, &coder_routine, &program->coders[i]);
		i++;
	}
	return (program);
}

void	create_objects(t_program **program)
{
	int	i;

	i = 0;
	while (i < (*program)->numbers_coders)
	{
		create_coders((*program), &(*program)->coders[i], i + 1);
		i++;
	}
	i = 0;
	while (i < (*program)->numbers_coders)
	{
		create_dongle(&(*program)->dongles[i], i + 1);
		i++;
	}
	(*program)->start_time = get_time();
}

void	free_engine(t_program *program)
{
	free(program->dongles);
	free(program->coders);
	free_heap(program->wait_heap);
	free(program);
}

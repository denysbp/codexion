/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:07 by deferrei          #+#    #+#             */
/*   Updated: 2026/09/06 20:00:13 by deferrei         ###   ########.fr       */
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
	create_objects(&program);
	program->start_time = get_time();
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
}

void	free_engine(t_program *program)
{
	destroy(&program);
	free(program->dongles);
	free(program->coders);
	free_heap(program->wait_heap);
	free(program);
}

void	destroy(t_program **program)
{
	int	i;

	i = 0;
	while (i < (*program)->numbers_coders)
	{
		pthread_mutex_destroy(&(*program)->coders[i].mutex);
		pthread_cond_destroy(&(*program)->coders[i].cond);
		i++;
	}
	pthread_mutex_destroy(&(*program)->mutex_dongle);
	pthread_mutex_destroy(&(*program)->mutex_print);
	pthread_mutex_destroy(&(*program)->mutex_state);
	pthread_cond_destroy(&(*program)->cond_dongles);
}

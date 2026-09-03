/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:32 by deferrei          #+#    #+#             */
/*   Updated: 2026/09/04 00:42:29 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

int	main(int argc, char **argv)
{
	t_error		error;
	t_program	*program;

	if (argc != 9)
	{
		program_usage();
		return (ERROR);
	}
	program = generator_engine(argv, &error);
	pthread_mutex_init(&error.mutex, NULL);
	if (!program)
	{
		print(error);
		free(error.str);
		return (ERROR);
	}
	if (!args_validation(&error, program))
	{
		print(error);
		return (ERROR);
	}
	scheduler(program);
	free_engine(program);
	return (0);
}

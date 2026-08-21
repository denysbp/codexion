/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:32 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/21 20:00:21 by deferrei         ###   ########.fr       */
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
	error.str = "";
	program = generator_engine(argv, &error);
	if (!program)
	{
		printf("%s\n", error.str);
		free(error.str);
		return (ERROR);
	}
	if (!args_validation(&error, program))
	{
		printf("%s\n", error.str);
		return (ERROR);
	}
	scheduler(program);
	free_engine(program);
	return (0);
}

#include "../../includes/codexion.h"

program_t	*generator_engine(char **argv, error_t *error)
{
	program_t	*program;
	int			i;

	i = 0;
	program = malloc(sizeof(program_t));
	if (save_args(argv, &program, error) == ERROR)
	{
		free(program);
		return (NULL);
	}
	program->coders = malloc(sizeof(coder_t) * program->numbers_coders);
	program->dongles = malloc(sizeof(dongle_t) * program->numbers_coders);
	pthread_mutex_init(&program->mutex_state, NULL);
	while (i < program->numbers_coders)
	{
		program->dongles[i] = create_dongles(i + 1);
		i++;
	}
	i = 0;
	while (i < program->numbers_coders)
	{
		program->coders[i] = create_coders(&program, i + 1);
		i++;
	}
	i = 0;
	while (i < program->numbers_coders)
	{
		pthread_create(&program->coders[i].coder, NULL, &coder_routine, &program->coders[i]);
		i++;
	}
	return (program);
}

void	free_engine(program_t *program)
{
	free(program->dongles);
	free(program->coders);
	free(program);
}
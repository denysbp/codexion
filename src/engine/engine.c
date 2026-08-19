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
	pthread_mutex_init(&program->mutex_dongle, NULL);
	pthread_cond_init(&program->cond_dongles, NULL);
	while (i < program->numbers_coders)
	{
		create_coders(program, &program->coders[i], i + 1);
		i++;
	}
	i = 0;
	while (i < program->numbers_coders)
	{
		create_dongle(&program->dongles[i], i + 1);
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
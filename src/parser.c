#include "../includes/codexion.h"


int	parser(const char *numbers_coders, error_t **error)
{
	int	value;

	if (invalid_numbers((const char*)numbers_coders))
	{
		(*error)->str = error_message("The numbers  must contain only NUMERS!!!");
		return (ERROR);
	}
	value = atoi(numbers_coders);
	if (value < 0)
	{
		(*error)->str = error_message("The numbers must be positive values");
		return (ERROR);
	}
	else if (!value)
	{
		return (0);
	}
	return (value);
}

int	save_args(char **argv, program_t **program, error_t *error)
{
	(*program)->numbers_coders = parser(argv[CODERS], &error);
	(*program)->time_to_burnout = parser(argv[TIME_BURNOUT], &error);
	(*program)->time_to_compile = parser(argv[TIME_COMPILE], &error);
	(*program)->time_to_debug = parser(argv[TIME_DEBUG], &error);
	(*program)->time_to_refactor = parser(argv[TIME_REFACTOR], &error);
	(*program)->numbers_of_compiles = parser(argv[NUMBER_COMPILES], &error);
	(*program)->dongle_cooldown = parser(argv[DONGLE_COOLDOWN], &error);
	(*program)->scheduler = argv[SCHEDULER];
	if (strcmp((*program)->scheduler, "fifo") != 0 && strcmp((*program)->scheduler, "edf") != 0)
	{
		error->str = error_message("Invalid type for scheduler");
		return (ERROR);
	}
	if ((*program)->numbers_coders == ERROR
        || (*program)->time_to_burnout == ERROR
        || (*program)->time_to_compile == ERROR
        || (*program)->time_to_debug == ERROR
        || (*program)->time_to_refactor == ERROR
        || (*program)->numbers_of_compiles == ERROR
        || (*program)->dongle_cooldown == ERROR)
        return (ERROR);
	return (0);
}

coder_t	create_coders(program_t	**program, int id)
{
	coder_t	coder;

	coder.id = id;
	coder.burned_out = false;
	coder.dongles = 0;
	coder.last_compile = 0;
	coder.left = &(*program)->dongles[id - 1];
	coder.right = &(*program)->dongles[((id - 1) + 1) % (*program)->numbers_coders];
	return (coder);
}

dongle_t	create_dongles(int id)
{
	dongle_t	dongle;

	dongle.id = id;
	pthread_mutex_init(&dongle.mutex_dongle, NULL);
	return (dongle);
}
program_t	*generator_engine(char **argv, error_t *error)
{
	program_t	*program;
	int			i;

	i = 0;
	program = malloc(sizeof(program_t));
	if (!program)
		return (NULL);
	if (save_args(argv, &program, error) == ERROR)
		return (NULL);
	program->coders = malloc(sizeof(coder_t) * program->numbers_coders);
	program->dongles = malloc(sizeof(dongle_t) * program->numbers_coders);
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
	return (program);
}

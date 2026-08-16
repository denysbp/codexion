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


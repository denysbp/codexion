#include "../includes/codexion.h"

int	main(int argc, char **argv)
{
	if (argc != 9)
	{
		program_usage();
		return (ERROR);
	}
	error_t	error;
	program_t	*program;
	heap_t		*heap;

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
	heap = heap_init(program->numbers_coders, program->scheduler, &program);
	free_heap(heap);
	free_engine(program);
	return (0);
}

#include "../includes/codexion.h"

int	main(int argc, char **argv)
{
	if (argc != 9)
	{
		printf("Program usage: ./codexion ");
		printf("number_of_coders time_to_burnout time_to_compile time_to_debug");
		printf("time_to_refactor number_of_compiles_required dongle_cooldown scheduler\n");
		return (-1);
	}
	error_t	error;
	program_t	*program;
	heap_t		*heap;

	error.str = "";
	program = generator_engine(argv, &error);
	heap = heap_init(program->numbers_coders, program->scheduler);
	if (!program)
	{
		printf("%s\n", error.str);
		return (-1);
	}
	// printf("%d\n", program->numbers_coders);
	// printf("%d\n", program->time_to_burnout);
	// printf("%d\n", program->time_to_compile);
	// printf("%d\n", program->time_to_debug);
	// printf("%d\n", program->time_to_refactor);
	// printf("%d\n", program->numbers_of_compiles);
	// printf("%d\n", program->dongle_cooldown);
	// printf("%s\n", program->scheduler);
	// printf("%d\n", program->runnig);
	printf("%s\n", heap->scheduler);
	printf("%d\n", heap->size);
	printf("%d\n", heap->capacity);
	free_engine(program);
	free_heap(heap);
	return (0);
}

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
	if (!program)
	{
		printf("%s\n", error.str);
		free(error.str);
		return (-1);
	}
	heap = heap_init(program->numbers_coders, program->scheduler);
	for (int i = program->numbers_coders - 1; i >= 0; i--)
	{
		heappush(&heap, &program->coders[i]);
	}
	printf("%d\n", heap->coders[0]->id);
	printf("%ld\n", heap->coders[0]->last_compile);
	free_heap(heap);
	free_engine(program);
	return (0);
}

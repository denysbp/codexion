#include "../../includes/codexion.h"

void	swap(coder_t **coder_a, coder_t **coder_b)
{
	coder_t	*tmp;

	tmp = *coder_a;
	*coder_a = *coder_b;
	*coder_b = tmp;
	return ;
}

int	has_priority(coder_t *coder_a, coder_t *coder_b, char *scheduler)
{
	if (!strcmp(scheduler, "fifo"))
	{
		return (coder_a->id < coder_b->id);
	}
	else if (!strcmp(scheduler, "edf"))
	{
		return (deadline(coder_a) < deadline(coder_b));
	}
	return (0);
}

void	free_heap(heap_t *heap)
{
	free(heap->coders);
	free(heap->scheduler);
	free(heap);
}
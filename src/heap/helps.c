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
	long	deadline_a;
	long	deadline_b;

	if (!strcmp(scheduler, "fifo"))
	{
		if (coder_a->request_time != coder_b->request_time)
		{
			return ((coder_a->request_time < coder_b->request_time));
		}
		return (coder_a->id < coder_b->id);
	}
	else if (!strcmp(scheduler, "edf"))
	{
		deadline_a = deadline(coder_a);
        deadline_b = deadline(coder_b);

        if (deadline_a != deadline_b)
            return (deadline_a < deadline_b);

        return (coder_a->id < coder_b->id);
	}
	return (0);
}

void	free_heap(heap_t *heap)
{
	free(heap->coders);
	free(heap->scheduler);
	free(heap);
}
#include "../includes/codexion.h"

heap_t	*heap_init(int capacity, char *scheduler)
{
	heap_t	*heap;

	heap = malloc(sizeof(heap_t));
	heap->coders = malloc(sizeof(coder_t *) * capacity);
	heap->size = 0;
	heap->capacity = capacity;
	heap->scheduler = ft_strcpy(scheduler);
	return (heap);
}

void	heapfy(heap_t **heap, int i, char *scheduler)
{
	int	priority;
	int	left;
	int	right;

	priority = i;
	left = 2 * i + 1;
	right = 2 * i + 2;

	if (left < (*heap)->size &&
		has_priority((*heap)->coders[left], (*heap)->coders[priority], scheduler))
		priority = left;

	if (right < (*heap)->size &&
		has_priority((*heap)->coders[right], (*heap)->coders[priority], scheduler))
		priority = right;

	if (priority != i)
	{
		swap(&(*heap)->coders[i], &(*heap)->coders[priority]);
		heapfy(heap, priority, scheduler);
	}
	return ;
}

void	heappush(heap_t	**heap, coder_t	*coder, char *scheduler)
{
	int	i;

	if ((*heap)->size == (*heap)->capacity)
		return ;

	(*heap)->size++;
	i = (*heap)->size - 1;
	(*heap)->coders[i] = coder;
	while (i != 0 && has_priority((*heap)->coders[i], (*heap)->coders[(i - 1) / 2], scheduler))
	{
		swap(&(*heap)->coders[i], &(*heap)->coders[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
	return ;
}


coder_t	*heappop(heap_t **heap,  char *scheduler)
{
	coder_t	*coder;

	if ((*heap)->size <= 0)
		return (NULL);
	if ((*heap)->size == 1)
	{
		(*heap)->size--;
		return ((*heap)->coders[0]);
	}
	coder = (*heap)->coders[0];
	(*heap)->coders[0] = (*heap)->coders[(*heap)->size - 1];
	(*heap)->size--;
	heapfy(heap, 0, scheduler);
	return (coder);
}

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
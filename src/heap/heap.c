#include "../../includes/codexion.h"

heap_t	*heap_init(int capacity, char *scheduler, program_t **program)
{
	heap_t	*heap;
	int		i;

	heap = malloc(sizeof(heap_t));
	heap->coders = malloc(sizeof(coder_t *) * capacity);
	heap->size = 0;
	heap->capacity = capacity;
	heap->scheduler = ft_strcpy(scheduler);
	pthread_mutex_init(&heap->mutex, NULL);
	i = 0;
	while (i < (*program)->numbers_coders)
	{
		heappush(&heap, &(*program)->coders[i]);
		i++;
	}
	return (heap);
}

void	heapfy(heap_t **heap, int i)
{
	int	priority;
	int	left;
	int	right;

	priority = i;
	left = 2 * i + 1;
	right = 2 * i + 2;

	if (left < (*heap)->size &&
		has_priority((*heap)->coders[left], (*heap)->coders[priority], (*heap)->scheduler))
		priority = left;

	if (right < (*heap)->size &&
		has_priority((*heap)->coders[right], (*heap)->coders[priority], (*heap)->scheduler))
		priority = right;

	if (priority != i)
	{
		swap(&(*heap)->coders[i], &(*heap)->coders[priority]);
		heapfy(heap, priority);
	}
	return ;
}

void	heappush(heap_t	**heap, coder_t	*coder)
{
	int	i;

	if ((*heap)->size == (*heap)->capacity)
		return ;

	(*heap)->size++;
	i = (*heap)->size - 1;
	(*heap)->coders[i] = coder;
	while (i != 0 && has_priority((*heap)->coders[i], (*heap)->coders[(i - 1) / 2], (*heap)->scheduler))
	{
		swap(&(*heap)->coders[i], &(*heap)->coders[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
	return ;
}


coder_t	*heappop(heap_t **heap)
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
	heapfy(heap, 0);
	return (coder);
}

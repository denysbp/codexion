#include "../includes/codexion.h"

heap_t	*heap_init(int capacity, char *scheduler)
{
	heap_t	*heap;

	heap = malloc(sizeof(heap_t));
	heap->coders = malloc(sizeof(coder_t) * capacity);
	heap->size = 0;
	heap->capacity = capacity;
	heap->scheduler = ft_strcpy(scheduler);
	return (heap);
}

// void	heapfy(heap_t **heap, int i)
// {
// 	return ;
// }

void	free_heap(heap_t *heap)
{
	free(heap->coders);
	free(heap);
	free(heap->scheduler);
}
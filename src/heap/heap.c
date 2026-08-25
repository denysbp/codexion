/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:15 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/25 14:49:54 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

t_heap	*heap_init(int capacity, char *scheduler, t_program **program)
{
	t_heap	*heap;
	int		i;

	heap = malloc(sizeof(t_heap));
	heap->coders = malloc(sizeof(t_coder *) * capacity);
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

t_heap	*wait_heap_init(int capacity, char *scheduler)
{
	t_heap	*heap;

	heap = malloc(sizeof(t_heap));
	heap->coders = malloc(sizeof(t_coder *) * capacity);
	heap->size = 0;
	heap->capacity = capacity;
	heap->scheduler = ft_strcpy(scheduler);
	pthread_mutex_init(&heap->mutex, NULL);
	return (heap);
}

void	heapfy(t_heap **heap, int i)
{
	int	priority;
	int	left;
	int	right;

	priority = i;
	left = 2 * i + 1;
	right = 2 * i + 2;
	if (left < (*heap)->size
		&& has_priority((*heap)->coders[left],
			(*heap)->coders[priority], (*heap)->scheduler))
		priority = left;
	if (right < (*heap)->size
		&& has_priority((*heap)->coders[right],
			(*heap)->coders[priority], (*heap)->scheduler))
		priority = right;
	if (priority != i)
	{
		swap(&(*heap)->coders[i], &(*heap)->coders[priority]);
		heapfy(heap, priority);
	}
	return ;
}

void	heappush(t_heap	**heap, t_coder	*coder)
{
	int	i;

	if ((*heap)->size == (*heap)->capacity)
		return ;
	(*heap)->size++;
	i = (*heap)->size - 1;
	(*heap)->coders[i] = coder;
	while (i != 0
		&& has_priority((*heap)->coders[i],
			(*heap)->coders[(i - 1) / 2], (*heap)->scheduler))
	{
		swap(&(*heap)->coders[i], &(*heap)->coders[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
	return ;
}

t_coder	*heappop(t_heap **heap)
{
	t_coder	*coder;

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

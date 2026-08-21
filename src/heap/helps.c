/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:18 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/21 19:59:33 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	swap(t_coder **coder_a, t_coder **coder_b)
{
	t_coder	*tmp;

	tmp = *coder_a;
	*coder_a = *coder_b;
	*coder_b = tmp;
	return ;
}

int	has_priority(t_coder *coder_a, t_coder *coder_b, char *scheduler)
{
	long	deadline_a;
	long	deadline_b;

	if (!strcmp(scheduler, "fifo"))
	{
		if (coder_a->request_order != coder_b->request_order)
		{
			return ((coder_a->request_order < coder_b->request_order));
		}
		return (coder_a->id < coder_b->id);
	}
	else if (!strcmp(scheduler, "edf"))
	{
		deadline_a = deadline(coder_a);
		deadline_b = deadline(coder_b);
		if (deadline_a != deadline_b)
		{
			return (deadline_a < deadline_b);
		}
		return (coder_a->id < coder_b->id);
	}
	return (0);
}

void	free_heap(t_heap *heap)
{
	free(heap->coders);
	free(heap->scheduler);
	free(heap);
}

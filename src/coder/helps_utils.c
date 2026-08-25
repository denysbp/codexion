/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:45:37 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/25 16:02:13 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

bool	coder_shares_dongle(t_coder *a, t_coder *b)
{
	return (a->left == b->left || a->left == b->right
		|| a->right == b->left || a->right == b->right);
}

bool	is_free(t_program *program, t_coder **coder)
{
	return (!(*coder)->right->free
		|| !(*coder)->left->free
		|| get_time() < (*coder)->right->cool_down
		|| get_time() < (*coder)->left->cool_down
		|| has_higher_priority_waiter(program->wait_heap, *coder));
}

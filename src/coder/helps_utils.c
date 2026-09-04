/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:45:37 by deferrei          #+#    #+#             */
/*   Updated: 2026/09/04 20:41:06 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

bool	coder_shares_dongle(t_coder *a, t_coder *b)
{
	return (a->left == b->left || a->left == b->right
		|| a->right == b->left || a->right == b->right);
}

bool	is_blocked(t_program *program, t_coder **coder)
{
	return (!(*coder)->right->free
		|| !(*coder)->left->free
		|| get_time() < (*coder)->right->cool_down
		|| get_time() < (*coder)->left->cool_down
		|| has_higher_priority_waiter(program->wait_heap, *coder));
}

bool	has_compiles(t_coder *coder)
{
	bool	result;

	pthread_mutex_lock(&coder->mutex);
	result = coder->compile_times < coder->program->numbers_of_compiles;
	pthread_mutex_unlock(&coder->mutex);
	return (result);
}

void	print(t_error error)
{
	printf("%s\n", error.str);
}

void	sucess(t_coder **coder)
{
	t_program	*program;

	program = (*coder)->program;
	(*coder)->right->free = false;
	print_save(program, "has taken a dongle", (*coder)->id);
	(*coder)->left->free = false;
	print_save(program, "has taken a dongle", (*coder)->id);
	(*coder)->dongles = 2;
}

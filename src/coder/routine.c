/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:01 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/26 14:05:07 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (has_compiles(coder) && is_running(coder->program))
	{
		take_dongle(&coder);
		if (is_stoping(&coder))
			return (NULL);
		compiling(&coder);
		if (is_stoping(&coder))
			return (NULL);
		debugging(&coder);
		if (is_stoping(&coder))
			return (NULL);
		refactoring(&coder);
		release_dongle(&coder);
	}
	return (NULL);
}

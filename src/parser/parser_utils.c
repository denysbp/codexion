/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:22 by deferrei          #+#    #+#             */
/*   Updated: 2026/08/21 19:42:07 by deferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

char	*error_message(const char *str)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * strlen(str) + 1);
	if (!new_str)
	{
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	return (new_str);
}

bool	signal(char c)
{
	return (c == '+' || c == '-');
}

bool	invalid_numbers(const char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9') && !signal(*str))
		{
			return (true);
		}
		str++;
	}
	return (false);
}

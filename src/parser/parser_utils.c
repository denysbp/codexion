/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deferrei <deferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 19:15:22 by deferrei          #+#    #+#             */
/*   Updated: 2026/09/04 00:40:50 by deferrei         ###   ########.fr       */
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
	new_str[i] = '\0';
	return (new_str);
}

bool	signal(char c)
{
	return (c == '+' || c == '-');
}

bool	invalid_numbers(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') && !signal(str[i]))
		{
			return (true);
		}
		i++;
	}
	if (strlen(str) >= 11 && strcmp(str, "2147483647") != 0)
		return (true);
	return (false);
}

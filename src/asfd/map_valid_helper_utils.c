/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_helper_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:21:13 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 13:30:12 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

int	new_lines(char *map)
{
	int	pos;
	int	nl;

	pos = 0;
	nl = 0;
	while (map[pos])
	{
		if (map[pos] == '\n')
			nl++;
		pos++;
	}
	return (nl);
}

int	line_len(char *map)
{
	int	line_before;
	int	len;
	int	pos;

	len = 0;
	pos = 0;
	while (map[pos])
	{
		line_before = 0;
		while (map[pos] && map[pos] != '\n')
		{
			line_before++;
			pos++;
		}
		if (len < line_before)
			len = line_before;
		if (map[pos])
			pos++;
	}
	return (len);
}

int	before(char *map, int height)
{
	int	breaker;
	int	inner;
	int	i;

	i = -1;
	breaker = 0;
	while (++i < height && breaker == 0)
	{
		inner = -1;
		while (map[++inner + i] && breaker == 0)
		{
			while (map[inner + i] == 32)
				inner++;
			if (map[inner + i] != 10)
				breaker = 1;
			else
				break ;
		}
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_helper3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 21:15:10 by yannis            #+#    #+#             */
/*   Updated: 2024/01/29 17:40:47 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

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

int	after(char *map, int line)
{
	int	pos;

	pos = 0;
	while (map[pos] && map[pos] == 10)
		pos++;
	pos--;
	while (map[pos])
	{
		if (map[pos] == 10)
		{
			pos++;
			while (map[pos] == SPACE)
				pos++;
			if (map[pos] == 10)
				break ;
			line++;
		}
		else
			pos++;
	}
	if (map[pos - 2] == '1' && map[pos - 1] == 10 && map[pos] == 0)
		line--;
	return (line);
}

int	longest_line(char *map, int height)
{
	int	line;
	int	pos;
	int	ll;

	pos = before(map, height) - 1;
	ll = 0;
	while (map[pos])
	{
		line = mpl(&map[pos]);
		pos += line;
		if (line > ll)
			ll = line;
		if (map[pos] == '\n')
			pos++;
	}
	return (ll + 1);
}

char	*true_size(char *map, int height)
{
	char	*str;
	int		ll;
	int		pos;
	int		pos2;

	ll = longest_line(map, height);
	pos = before(map, height) - 1;
	str = (char *)malloc(((after(map, pos) - pos) * ll) + 1);
	if (!str)
		return (perror("Error\nAllocation failed"), NULL);
	pos2 = 0;
	pos = pos2;
	return (str);
}

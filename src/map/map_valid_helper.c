/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:42:43 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 13:00:54 by abied-ch         ###   ########.fr       */
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

static	int	line_len(char *map)
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

static	int	before(char *map, int height)
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

static	int	after(char *map, int line)
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
			while (map[pos] == 32)
				pos++;
			if (map[pos] == 10)
				break;
			line++;
		}
		else
			pos++;
	}
	if (map[pos - 2] == '1' && map[pos - 1] == 10 && map[pos] == 0)
		line--;
	return (line);
}

static	int	longest_line(char *map, int height)
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

static	char	*true_size(char *map, int height)
{
	char	*str;
	int		ll;
	int		pos;
	int		pos2;

	ll = longest_line(map, height);
	pos = before(map, height) - 1;
	str = (char *)malloc(((after(map, pos) - pos) * ll));
	if (!str)
		return (free(map), perror("Error\nAlloc failed in true_size"), NULL);
	pos2 = 0;
	pos = pos2;
	return (str);
}

static	char	*fixed_box(char *map, int height, int index)
{
	char	*str;
	int		box_size;
	int		pos;
	int		ll;
	int		line;

	str = true_size(map, height);
	if (!str)
		return (NULL);
	pos = before(map, height) - 1;
	ll = longest_line(map, height);
	box_size = ((after(map, pos) - pos) * ll) + 1;
	while (map[pos] && index < box_size - 1)
	{
		line = 0;
		while (map[pos] && map[pos] != 10 && index < box_size - 1)
		{
			str[index++] = map[pos++];
			line++;
		}
		while (line < ll - 1 && index < box_size - 1)
		{
			str[index++] = ' ';
			line++;
		}
		if (map[pos])
			str[index++] = map[pos++];
	}
	str[index] = 0;
	return (str);
}

char	*fixed(char *origin)
{
	char	*new;
	int		height;
	int		len;

	len = line_len(origin);
	height = new_lines(origin);
	new = fixed_box(origin, height, 0);
	free(origin);
	if (!new)
		return (NULL);
	if (check_map_if_valid(new, -1, 0) < 0)
		return (free(new), NULL);
	if (check_player_in_map(new) < 0)
		return (free(new), NULL);
	return (new);
}

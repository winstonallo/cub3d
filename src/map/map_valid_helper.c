/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:42:43 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 13:22:40 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

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

static	char	*fixed_box(char *str, char *map, int height, int index)
{
	int		box_size;
	int		pos;
	int		ll;
	int		line;

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
		while (line++ < ll - 1 && index < box_size - 1)
			str[index++] = ' ';
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
	char	*str;

	len = line_len(origin);
	height = new_lines(origin);
	str = true_size(origin, height);
	if (!str)
		return (NULL);
	new = fixed_box(str, origin, height, 0);
	free(origin);
	if (!new)
		return (NULL);
	if (check_map_if_valid(new, -1, 0) < 0)
		return (free(new), NULL);
	if (check_player_in_map(new) < 0)
		return (free(new), NULL);
	return (new);
}

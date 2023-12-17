/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:42:43 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/17 12:44:11 by abied-ch         ###   ########.fr       */
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

static	void	replace_char(t_map *struct_map, char *map, char *str, char cha)
{
	while (map[struct_map->pos] && map[struct_map->pos] != '\n')
	{
		struct_map->stepper++;
		if (map[struct_map->pos] == ' ')
			str[struct_map->pos2] = cha;
		else
			str[struct_map->pos2] = map[struct_map->pos];
		struct_map->pos++;
		struct_map->pos2++;
	}
}

static	char	*fixed_box(char *map, int height, int len)
{
	t_map	struct_map;
	char	*str;

	str = (char *)malloc(((height + 2) * len) + height + 1);
	if (!str)
		return (printf("Error\nAlloc failed in fixed_box\n"), NULL);
	struct_map.pos2 = 0;
	struct_map.pos = 0;
	struct_map.nl = 0;
	while (map[struct_map.pos] && struct_map.nl < height + 2)
	{
		struct_map.stepper = -1;
		struct_map.fill = 0;
		replace_char(&struct_map, map, str, ' ');
		while (++struct_map.fill < ((struct_map.stepper - len) * -1))
			str[struct_map.pos2++] = ' ';
		if (map[struct_map.pos] == '\n' && struct_map.nl < height)
			str[struct_map.pos2++] = '\n';
		struct_map.pos++;
		struct_map.nl++;
	}
	str[struct_map.pos2] = 0;
	return (str);
}

char	*fixed(char *origin)
{
	char	*new;
	int		height;
	int		len;

	len = line_len(origin);
	height = new_lines(origin);
	new = fixed_box(origin, height, len);
	free(origin);
	if (!new)
		return (NULL);
	if (check_map_if_valid(new) < 0)
		return (free(new), NULL);
	if (check_player_in_map(new) < 0)
		return (free(new), NULL);
	new = remove_nls(new);
	return (new);
}

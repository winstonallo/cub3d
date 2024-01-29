/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:42:43 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 18:50:33 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

int	mpl(char *map);

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

static	char	*fixed_box(char *map, int height, t_fixed_struct f)
{
	f.str = true_size(map, height);
	if (!f.str)
		return (NULL);
	f.pos = before(map, height) - 1;
	f.box_size = ((after(map, f.pos) - f.pos) * f.ll) + 1;
	f.index = 0;
	while (map[f.pos] && f.index < f.box_size - 1)
	{
		f.line = 0;
		while (map[f.pos] && map[f.pos] != 10 && f.index < f.box_size - 1)
		{
			f.str[f.index++] = map[f.pos++];
			f.line++;
		}
		while (f.line < f.ll - 1 && f.index < f.box_size - 1)
		{
			f.str[f.index++] = ' ';
			f.line++;
		}
		if (map[f.pos])
			f.str[f.index++] = map[f.pos++];
	}
	f.str[f.index] = 0;
	return (f.str);
}

char	*fixed(char *origin)
{
	t_fixed_struct	fixed_s;
	char			*new;
	int				height;
	int				pos;
	int				nl;

	height = new_lines(origin);
	fixed_s.ll = longest_line(origin, height);
	new = fixed_box(origin, height, fixed_s);
	free(origin);
	if (!new)
		return (NULL);
	pos = -1;
	while (new[++pos])
		;
	nl = 0;
	if (new[pos - 1] == '\n')
		nl = 1;
	if (check_map_if_valid(new, -1, 0, nl) < 0)
		return (free(new), NULL);
	if (check_player_in_map(new) < 0)
		return (free(new), NULL);
	return (new);
}

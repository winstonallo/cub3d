/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:42:26 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/23 21:10:21 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

static	char	*replace_hex(char *loaded)
{
	char	*replace;
	int		pos;

	pos = 0;
	replace = (char *)malloc(ft_strlen(loaded) + 1);
	if (!replace)
		return (perror("Error\nAlloc failed in replace"), NULL);
	while (loaded[pos])
	{
		if (loaded[pos] == '0')
			replace[pos] = 'X';
		else
			replace[pos] = loaded[pos];
		pos++;
	}
	replace[pos] = 0;
	return (replace);
}

int	mpl(char *map);

int	check_map_if_valid(char *m)
{
	int	i;
	int	leaks;

	i = -1;
	leaks = 0;
	while (m[++i])
	{
		if (m[i] == 'X')
			if ((m[i - 1] != 'X' && m[i - 1] != '1' && m[i - 1] != 'N'
					&& m[i - 1] != 'S' && m[i - 1] != 'W' && m[i - 1] != 'E'
					&& m[i - 1] != 'U' && m[i - 1] != 'L' && m[i - 1] != 'R')
				|| (m[i + 1] != 'X' && m[i + 1] != '1' && m[i + 1] != 'N'
					&& m[i + 1] != 'S' && m[i + 1] != 'W' && m[i + 1] != 'E'
					&& m[i - 1] != 'U' && m[i - 1] != 'L' && m[i - 1] != 'R')
				|| (m[i - mpl(m)] != 'X' && m[i - mpl(m)] != '1'
					&& m[i - mpl(m)] != 'N' && m[i - mpl(m)] != 'S'
					&& m[i - mpl(m)] != 'W' && m[i - mpl(m)] != 'E'
					&& m[i - mpl(m)] != 'U' && m[i - mpl(m)] != 'L'
					&& m[i - mpl(m)] != 'R')
				|| (m[i + mpl(m)] != 'X' && m[i + mpl(m)] != '1'
					&& m[i + mpl(m)] != 'N' && m[i + mpl(m)] != 'S'
					&& m[i + mpl(m)] != 'W' && m[i + mpl(m)] != 'E'
					&& m[i + mpl(m)] != 'U' && m[i + mpl(m)] != 'L'
					&& m[i + mpl(m)] != 'R'))
				leaks++;
	}
	if (leaks > 0)
		return (printf("Error\n%i leaks found\n", leaks), perror(""), -1);
	return (0);
}

int	check_player_in_map(char *map)
{
	int	pos;

	pos = 0;
	while (map[pos])
	{
		if (map[pos] == 'N' || map[pos] == 'S'
			|| map[pos] == 'E' || map[pos] == 'W')
		{
			if ((map[pos - mpl(map)] != '1' && map[pos - mpl(map)] != 'X'
					&& map[pos - mpl(map)] != 'U' && map[pos - mpl(map)] != 'L'
					&& map[pos - mpl(map)] != 'R')
				|| (map[pos + mpl(map)] != '1' && map[pos + mpl(map)] != 'X'
					&& map[pos + mpl(map)] != 'U' && map[pos + mpl(map)] != 'L'
					&& map[pos + mpl(map)] != 'R')
				|| (map[pos + 1] != '1' && map[pos + 1] != 'X' && map[pos + 1] != 'U'
					 && map[pos + 1] != 'L' && map[pos + 1] != 'R')
				|| (map[pos - 1] != '1' && map[pos - 1] != 'X' && map[pos - 1] != 'U'
					 && map[pos - 1] != 'L' && map[pos - 1] != 'R'))
				return (perror("Error\nPlayer out of map"), -1);
		}
		pos++;
	}
	return (0);
}

char	*map_valid(char *loaded)
{
	char	*changed;

	changed = replace_hex(loaded);
	free(loaded);
	if (!changed)
		return (NULL);
	changed = fixed(changed);
	if (!changed)
		return (NULL);
	return (changed);
}

int	*map_main(char *map, t_data *data)
{
	int	*sliced_map;

	if (check_if_exists(map) < 0)
		return (NULL);
	if (check_if_valid(map, data) < 0)
		return (NULL);
	sliced_map = slice_map(map);
	if (!sliced_map)
		return (NULL);
	return (sliced_map);
}

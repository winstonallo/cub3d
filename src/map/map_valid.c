/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:42:26 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/21 16:58:39 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

static char	*replace(char *loaded)
{
	char	*replace;
	int		pos;

	pos = 0;
	replace = (char *)malloc(ft_strlen(loaded) + 1);
	if (!replace)
		return (printf("Error\nAlloc failed in replace"), NULL);
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
		{
			if ((m[i - 1] != 'X' && m[i - 1] != '1' && m[i - 1] != 'N'
					&& m[i - 1] != 'S' && m[i - 1] != 'W' && m[i - 1] != 'E')
				|| (m[i + 1] != 'X' && m[i + 1] != '1' && m[i + 1] != 'N'
					&& m[i + 1] != 'S' && m[i + 1] != 'W' && m[i + 1] != 'E')
				|| (m[i - mpl(m)] != 'X' && m[i - mpl(m)] != '1'
					&& m[i - mpl(m)] != 'N' && m[i - mpl(m)] != 'S'
					&& m[i - mpl(m)] != 'W' && m[i - mpl(m)] != 'E')
				|| (m[i + mpl(m)] != 'X' && m[i + mpl(m)] != '1'
					&& m[i + mpl(m)] != 'N' && m[i + mpl(m)] != 'S'
					&& m[i + mpl(m)] != 'W' && m[i + mpl(m)] != 'E'))
				leaks++;
		}
	}
	if (leaks > 0)
		return (printf("Error\n%i leaks found\n", leaks), -1);
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
			if ((map[pos - mpl(map)] != '1' && map[pos - mpl(map)] != 'X')
				|| (map[pos + mpl(map)] != '1' && map[pos + mpl(map)] != 'X')
				|| (map[pos + 1] != '1' && map[pos + 1] != 'X')
				|| (map[pos - 1] != '1' && map[pos - 1] != 'X'))
				return (printf("Error\nPlayer out of map\n"), -1);
		}
		pos++;
	}
	return (0);
}

char	*map_valid(char *loaded)
{
	char	*changed;

	changed = replace(loaded);
	free(loaded);
	if (!changed)
		return (NULL);
	changed = fixed(changed);
	if (!changed)
		return (NULL);
	return (changed);
}

int	*map_main(char *map)
{
	int	*sliced_map;

	if (check_if_exists(map) < 0)
		return (NULL);
	if (check_if_valid(map) < 0)
		return (NULL);
	sliced_map = slice_map(map);
	if (!sliced_map)
		return (NULL);
	return (sliced_map);
}

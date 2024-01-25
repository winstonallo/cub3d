/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:42:26 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 12:58:55 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"
#include <unistd.h>

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

int	check_map_if_valid(char *m, int i, int leaks)
{
	while (m[++i])
		if (m[i] == 'X')
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
	if (leaks > 0)
		return (ft_putstr_fd("Error\nPlayer not enclosed in map\n", 2), -1);
	return (0);
}

int	check_player_in_map(char *map)
{
	int		pos;

	pos = 0;
	while (map[pos])
	{
		if (ft_strchr("NSEW", map[pos]))
		{
			if (!ft_strchr("1X", map[pos - mpl(map)]) || !ft_strchr("1X",
					map[pos + mpl(map)]) || !ft_strchr("1X", map[pos + 1])
				|| !ft_strchr("1X", map[pos - 1]))
			{
				ft_putstr_fd("Error\nPlayer outside of the map", STDERR_FILENO);
				return (-1);
			}
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

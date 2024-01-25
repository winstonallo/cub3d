/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:42:26 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 17:41:06 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

int	check_multiple_chars(char character, char *to_find)
{
	int	found;
	int	pos;

	pos = -1;
	found = 0;
	while (to_find[++pos])
	{
		if (character == to_find[pos])
			found++;
	}
	if (found < 1)
		return (-1);
	return (0);
}

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

int	check_map_if_valid(char *m, int i, int leaks)
{
	while (m[++i])
		if (m[i] == 'X')
			if (check_multiple_chars(m[i - 1], "X1NWES") < 0
				|| check_multiple_chars(m[i + 1], "X1NWES") < 0
				|| check_multiple_chars(m[i - mpl(m) - 1], "X1NWES") < 0
				|| check_multiple_chars(m[i + mpl(m) + 1], "X1NWES") < 0)
				leaks++;
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
				return (ft_putstr_fd("Error\nPlayer out of map", 2), -1);
		}
		pos++;
	}
	return (0);
}

char	*map_valid(char *loaded, t_data *data)
{
	char	*changed;
	int		pos;

	changed = replace_hex(loaded);
	free(loaded);
	if (!changed)
		return (NULL);
	changed = fixed(changed);
	if (!changed)
		return (NULL);
	pos = 0;
	while (changed[pos])
		pos++;
	data->map_width = mpl(changed);
	data->map_height = (pos / (data->map_width + 1)) + 1;
	return (changed);
}

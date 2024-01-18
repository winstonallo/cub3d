/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:41:54 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/18 18:50:52 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

static	char	*remove_textures_and_rgb(char *map)
{
	char	*new;
	int		i;
	int		j;
	int		nl;

	nl = 0;
	i = 0;
	while (map[i])
	{
		if (nl == 7)
			break ;
		if (map[i] == '\n')
			nl++;
		i++;
	}
	new = (char *)malloc((ft_strlen(map) - (i + 1)) + 2);
	if (!new)
		return (printf("Error\nAllocation failed in rem_txt_rgb"), NULL);
	j = 0;
	while (map[i])
		new[j++] = map[i++];
	new[j] = 0;
	return (new);
}

static char	*check_for_invalid_textures(char *origin)
{
	char	*temp;
	int		valid;
	int		pos;

	temp = ft_strdup(origin);
	if (!temp)
		return (printf("Error\nAlloc failed in c_f_i_t\n"), free(origin), NULL);
	pos = 0;
	valid = 0;
	while (temp[pos])
	{
		if (!(temp[pos] == '1' || temp[pos] == '0' || temp[pos] == 'N'
				|| temp[pos] == 'W' || temp[pos] == 'S' || temp[pos] == 'E'
				|| temp[pos] == '\n' || temp[pos] == ' ' || temp[pos] == 0 || temp[pos] == '2'))
			valid--;
		pos++;
	}
	free(origin);
	if (valid < 0)
	{
		printf("Error\nMap invalid. Invalid character found\n");
		free(temp);
		temp = NULL;
	}
	return (temp);
}

static	int	check_for_multiple_player(char *origin)
{
	int	player_count;
	int	pos;

	player_count = 0;
	pos = 0;
	while (origin[pos])
	{
		if (origin[pos] == 'N' || origin[pos] == 'W'
			|| origin[pos] == 'E' || origin[pos] == 'S')
			player_count++;
		pos++;
	}
	if (player_count == 0)
		return (printf("Error\nNo player found\n"), -1);
	else if (player_count > 1)
		return (printf("Error\nToo many players on map\n"), -1);
	return (1 - player_count);
}

static char	*check_map(char *map)
{
	char	*modified;

	modified = remove_textures_and_rgb(map);
	if (!modified)
		return (NULL);
	modified = check_for_invalid_textures(modified);
	if (!modified)
		return (NULL);
	if (check_for_multiple_player(modified) < 0)
		return (NULL);
	return (modified);
}

int	*slice_map(char *map)
{
	char	*loaded_map;
	char	*updated;
	int		*slice;
	int		fd;

	fd = open(map, O_RDONLY);
	loaded_map = load_map(fd);
	if (!loaded_map)
		return (printf("Error\nCan't load map in slice_map"), close(fd), NULL);
	updated = check_map(loaded_map);
	if (!updated)
		return (NULL);
	free(loaded_map);
	updated = map_valid(updated);
	if (!updated)
		return (NULL);
	slice = slicer(updated);
	free(updated);
	if (!slice)
		return (NULL);
	close(fd);
	return (slice);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:41:54 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 16:30:59 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"
#include <unistd.h>

static	char	*remove_textures_and_rgb(char *map, int *nl)
{
	char	*new;
	int		nl_inner;
	int		i;
	int		j;

	nl_inner = 0;
	i = 0;
	while (map[i])
	{
		if (nl_inner == *nl)
			break ;
		if (map[i] == '\n')
			nl_inner++;
		i++;
	}
	new = (char *)malloc((ft_strlen(map) - (i + 1)) + 2);
	if (!new)
		return (perror("Error\nAllocation failed in rem_txt_rgb"), NULL);
	j = 0;
	while (map[i])
		new[j++] = map[i++];
	new[j] = 0;
	return (new);
}

static int	check_for_invalid_textures(char *origin)
{
	int	pos;

	pos = 0;
	while (origin[pos])
	{
		if (!(origin[pos] == '1' || origin[pos] == '0'
				|| origin[pos] == 'N' || origin[pos] == 'W'
				|| origin[pos] == 'S' || origin[pos] == 'E'
				|| origin[pos] == '\n' || origin[pos] == ' '
				|| origin[pos] == 0))
			return (ft_putstr_fd("Error\nInvalid character found\n", 2), -1);
		pos++;
	}
	return (0);
}

static	int	check_for_multiple_player(char *origin)
{
	int	player_count;
	int	pos;

	if (ft_strlen(origin) < 1)
		return (ft_putendl_fd("Error\nNo map in file", STDERR_FILENO), -1);
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
		return (ft_putendl_fd("Error\nNo player found", STDERR_FILENO), -1);
	else if (player_count > 1)
		return (ft_putendl_fd("Error\nToo many players", STDERR_FILENO), -1);
	return (1 - player_count);
}

static char	*check_map(char *map, int *nl)
{
	char	*modified;

	modified = remove_textures_and_rgb(map, nl);
	if (!modified)
		return (NULL);
	if (check_for_invalid_textures(modified) < 0)
		return (free(modified), NULL);
	if (check_for_multiple_player(modified) < 0)
		return (free(modified), NULL);
	return (modified);
}

int	*slice_map(char *map, t_data *data, int *nl)
{
	char	*loaded_map;
	char	*updated;
	int		*slice;
	int		fd;

	fd = open(map, O_RDONLY);
	loaded_map = load_map(fd);
	if (!loaded_map)
		return (close(fd), NULL);
	updated = check_map(loaded_map, nl);
	free(loaded_map);
	if (!updated)
		return (close(fd), NULL);
	updated = map_valid(updated, data);
	if (!updated)
		return (close(fd), NULL);
	slice = slicer(updated);
	free(updated);
	if (!slice)
		return (close(fd), NULL);
	close(fd);
	return (slice);
}

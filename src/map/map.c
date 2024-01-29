/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:41:12 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 14:14:49 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

char	*load_map(int fd);
void	*get_texture_helper(t_texture *texture, char *loaded, char **params);
void	m_matrix_free(char **error_names);
int		*map_main(char *map, t_data *data);
int		get_rgb_helper(t_texture *texture, char *loaded, char **params);
int		map_get_player(int *map);
char	**fill_params(int flag);

int	*map(char *map, t_data *data)
{
	int	*result;

	result = map_main(map, data);
	return (result);
}

int	map_get_player_pos(int *map)
{
	int	result;

	result = map_get_player(map);
	return (result);
}

t_texture	map_get_textures(char *map)
{
	t_texture	texture;
	char		**params;
	char		*loaded;
	int			fd;

	fd = open(map, O_RDONLY);
	loaded = load_map(fd);
	texture.err_code = 1;
	if (!loaded)
		return (close(fd), perror("Error\nAllocation failed\n"), texture);
	close(fd);
	params = fill_params(0);
	if (!params)
		return (printf("Error\nAllocation failed"), texture);
	if (get_texture_helper(&texture, loaded, params) < 0)
		return (free(loaded), m_matrix_free(params), texture);
	if (get_rgb_helper(&texture, loaded, params) < 0)
		return (free(loaded), m_matrix_free(params), texture);
	free(loaded);
	m_matrix_free(params);
	texture.err_code = 0;
	return (texture);
}

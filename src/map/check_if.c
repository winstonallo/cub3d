/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:39:46 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/23 21:13:36 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

char	*input(char *map);

int	check_if_exists(char *map)
{
	int	fd;
	int	counter;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nMap-file invalid\n"), -1);
	counter = 0;
	while (map[counter])
		counter++;
	if (!(map[counter - 4] == '.' && map[counter - 3] == 'c'
			&& map[counter - 2] == 'u' && map[counter - 1] == 'b'))
		return (printf("Error\nMap-file not compatible"),
			printf("with cub3d. Please use .cub files\n"), -1);
	return (fd);
}

static	char	**check_if_all_textures_available(char *loaded_map, char **err)
{
	char	**params;
	int		pos;

	params = fill_params(0);
	if (!params)
		return (NULL);
	pos = check_if_all_textures_helper(params, err, loaded_map);
	if (pos < 0)
		return (m_matrix_free(params), NULL);
	return (params);
}

static	int	check_if_all_textures_valid(char *map, char **tags, char **error, t_data *data)
{
	t_check	*check;
	int		valid;
	int		pos;

	check = (t_check *)malloc(sizeof(t_check));
	if (!check)
		return (printf("Error\nAllocation failed\n"), -1);
	valid = 4;
	pos = -1;
	while (++pos < 4)
	{
		check->change = 0;
		if (check_for(check, map, tags, pos) != 0)
			return (free(check), -1);
		check->str = copy(ft_strnstr(map, tags[pos],
					ft_strlen(map)) + 3, check->fd);
		if (!check->str)
			return (free(check), -1);
		if (check->change != 0)
			check->str[4] = 32;
		valid = validate_file(check->str, valid, error, pos, data);
		free(check->str);
	}
	free(check);
	return (valid - 4);
}

static	int	check_if_all_colors_valid(char *m, char **tags, char **error)
{
	t_check	*c;
	int		vp[2];

	c = (t_check *)malloc(sizeof(t_check));
	if (!c)
		return (perror("Error\nAllocation failed in check_all_color_valid"), -1);
	vp[1] = 2;
	vp[0] = -1;
	while (++vp[0] < 2)
	{
		c->change = 0;
		if (check_for(c, m, tags, vp[0] + 4) != 0)
			return (free(c), -1);
		c->str = copy(ft_strnstr(m, tags[vp[0] + 4], ft_strlen(m)) + 2, c->fd);
		if (!c->str)
			return (free(c), -1);
		if (c->change != 0)
			c->str[4] = 32;
		vp[1] = validate_rgb(c->str, vp[1], error, vp[0] + 4);
		if (vp[1] == -1)
			return (free(c->str), free(c), -1);
		free(c->str);
	}
	free(c);
	return (vp[1] - 2);
}

int	check_if_valid(char *map, t_data *data)
{
	char	**error_params;
	char	**tags;
	char	*open_map;
	int		fd;

	fd = open(map, O_RDONLY);
	open_map = load_map(fd);
	if (!open_map)
		return (close(fd), perror("Error\nAllocation failed. Could not load map\n"), -1);
	error_params = fill_params(1);
	if (!error_params)
		return (close(fd), free(open_map), -1);
	tags = check_if_all_textures_available(open_map, error_params);
	if (!tags)
		return (m_matrix_free(error_params), free(open_map), -1);
	if (check_if_all_textures_valid(open_map, tags, error_params, data) < 0)
		return (m_matrix_free(error_params), m_matrix_free(tags), free(open_map), -1);
	if (check_if_all_colors_valid(open_map, tags, error_params) < 0)
		return (m_matrix_free(error_params), m_matrix_free(tags), free(open_map),-1);
	m_matrix_free(error_params);
	m_matrix_free(tags);
	free(open_map);
	close(fd);
	return (0);
}

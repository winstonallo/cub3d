/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:39:46 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 13:26:35 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

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

static	int	check_if_all_textures_valid(char *m, char **t, char **er, t_data *d)
{
	t_check	*check;
	int		valid;

	check = (t_check *)malloc(sizeof(t_check));
	if (!check)
		return (printf("Error\nAllocation failed\n"), -1);
	valid = 4;
	d->map_vars.pos = -1;
	while (++d->map_vars.pos < 4)
	{
		check->change = 0;
		if (check_for(check, m, t, d->map_vars.pos) != 0)
			return (free(check), -1);
		check->str = copy(ft_strnstr(m, t[d->map_vars.pos],
					ft_strlen(m)) + 3, check->fd);
		if (!check->str)
			return (free(check), -1);
		if (check->change != 0)
			check->str[4] = 32;
		valid = validate_file(check->str, valid, er, d);
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
		return (perror("Error\nAllocation failed in color validation"), -1);
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
	char	**err_p;
	char	**tags;
	char	*o_m;
	int		fd;

	fd = open(map, O_RDONLY);
	o_m = load_map(fd);
	if (!o_m)
		return (close(fd), perror("Error\nAllocation failed\n"), -1);
	err_p = fill_params(1);
	if (!err_p)
		return (close(fd), free(o_m), -1);
	tags = check_if_all_textures_available(o_m, err_p);
	if (!tags)
		return (m_matrix_free(err_p), free(o_m), -1);
	if (check_if_all_textures_valid(o_m, tags, err_p, data) < 0)
		return (m_matrix_free(err_p), m_matrix_free(tags), free(o_m), -1);
	if (check_if_all_colors_valid(o_m, tags, err_p) < 0)
		return (m_matrix_free(err_p), m_matrix_free(tags), free(o_m), -1);
	m_matrix_free(err_p);
	m_matrix_free(tags);
	free(o_m);
	close(fd);
	return (0);
}

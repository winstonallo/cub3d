/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:39:46 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 18:03:47 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

int	check_if_exists(char *map)
{
	int	fd;
	int	counter;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (perror("Error\nMap-file invalid\n"), -1);
	counter = 0;
	while (map[counter])
		counter++;
	if (!(map[counter - 4] == '.' && map[counter - 3] == 'c'
			&& map[counter - 2] == 'u' && map[counter - 1] == 'b'))
		return (ft_putstr_fd("Error\nMap-file not compatible ", 2), -1);
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

static	int	check_textures(char *map, char **tags, t_data *data)
{
	t_check	check;
	char	*temp;

	check.valid = 4;
	check.pos = -1;
	while (++check.pos < 4)
	{
		check.change = 0;
		if (check_for(&check, map, tags, check.pos) != 0)
			return (-1);
		temp = ft_strnstr(map, tags[check.pos],
				ft_strlen(map))
			+ skip(ft_strnstr(map, tags[check.pos], ft_strlen(map)));
		check.str = copy(temp, len(temp));
		if (!check.str)
			return (-1);
		check.valid = validate_file(&check, data);
	}
	return (check.valid - 4);
}

static	int	check_if_all_colors_valid(char *m, char **tags, t_data *data)
{
	t_check	c;
	int		vp[2];
	char	*temp;
	char	ch;

	vp[1] = 2;
	vp[0] = -1;
	while (++vp[0] < 2)
	{
		if (check_for(&c, m, tags, vp[0] + 4) != 0)
			return (-1);
		temp = ft_strnstr(m, tags[vp[0] + 4], ft_strlen(m))
			+ skip(ft_strnstr(m, tags[vp[0] + 4], ft_strlen(m)));
		c.str = copy(temp, len(temp));
		if (!c.str)
			return (-1);
		ch = (ft_strnstr(m, tags[vp[0] + 4], ft_strlen(m)))[0];
		vp[1] = validate_rgb(c.str, vp[1], data, ch);
		if (vp[1] == -1)
			return (free(c.str), -1);
		free(c.str);
	}
	return (vp[1] - 2);
}

int	check_if_valid(char *map, t_data *data)
{
	char	**err_param;
	char	**tags;
	char	*o_m;
	int		fd;

	fd = open(map, O_RDONLY);
	o_m = load_map(fd);
	if (!o_m)
		return (close(fd), perror("Error\nAllocation failed\n"), -1);
	err_param = fill_params(1);
	if (!err_param)
		return (close(fd), free(o_m), -1);
	tags = check_if_all_textures_available(o_m, err_param);
	if (!tags)
		return (m_matrix_free(err_param), free(o_m), -1);
	if (check_textures(o_m, tags, data) < 0)
		return (m_matrix_free(err_param), m_matrix_free(tags), free(o_m), -1);
	if (check_if_all_colors_valid(o_m, tags, data) < 0)
		return (m_matrix_free(err_param), m_matrix_free(tags), free(o_m), -1);
	m_matrix_free(err_param);
	m_matrix_free(tags);
	free(o_m);
	close(fd);
	return (0);
}

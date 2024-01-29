/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:40:52 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 19:03:20 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"
#include <stdio.h>

char	*load_map(int fd)
{
	char	*map;
	char	*t_char;
	int		single;

	map = (char *)malloc(sizeof(char) * 1);
	if (!map)
		return (perror("Error\nAllocation failed"), NULL);
	map[0] = 0;
	while (1)
	{
		single = 0;
		if (read(fd, &single, 1) == -1)
			return (free(map), perror("Error\nRead failed"), NULL);
		if (single < 32 && single != '\n')
			break ;
		t_char = malloc(2);
		if (!t_char)
			return (free(map), perror("Error\nAllocation failed"), NULL);
		t_char[0] = single;
		t_char[1] = 0;
		map = str_join_block(map, t_char);
		if (!map)
			return (perror("Error\nAllocation failed"), NULL);
	}
	return (check_only_spaces(map));
}

char	*copy(char *to_copy, int size)
{
	char	*new;
	int		pos;

	new = (char *)ft_calloc(size + 2, sizeof(char));
	if (!new)
		return (perror("Error\nAllocation failed"), NULL);
	pos = 0;
	while (pos < size)
	{
		new[pos] = to_copy[pos];
		pos++;
	}
	new[pos] = 0;
	return (new);
}

static	char	*convert_rgb_to_hex(char *before)
{
	char	**rgb;
	char	*value;
	int		i[2];

	rgb = ft_split(before, ',');
	if (!rgb)
		return (perror("Error\nAllocation failed"), NULL);
	value = (char *)malloc(9);
	if (!value)
		return (perror("Error\nAllocation failed"), NULL);
	i[1] = -1;
	while (rgb[++i[1]])
	{
		i[0] = ft_atoi(rgb[i[1]]);
		if ((i[0] / 16) < 10)
			value[(i[1] * 2) + 2] = (i[0] / 16) + '0';
		else
			value[(i[1] * 2) + 2] = (i[0] / 16) + 87;
		if ((i[0] % 16) < 10)
			value[(i[1] * 2) + 3] = (i[0] % 16) + '0';
		else
			value[(i[1] * 2) + 3] = (i[0] % 16) + 87;
	}
	value[8] = 0;
	return (m_matrix_free(rgb), value);
}

int	get_texture_helper(t_texture *texture, char *loaded, char **params)
{
	char	*temp;
	int		walker;
	int		i;

	i = -1;
	while (++i < 4)
	{
		walker = 0;
		temp = ft_strdup(ft_strnstr(loaded, params[i], ft_strlen(loaded)) + 3);
		if (!temp)
			return (perror("Error\nAllocation failed"), -1);
		while (temp[walker] && temp[walker] != ' ' && temp[walker] != '\n')
			walker++;
		temp[walker] = 0;
		texture->texture_fds[i] = open(temp, O_RDONLY);
		free(temp);
		if (texture->texture_fds[i] < 0)
		{
			while (--i >= 0)
				close(texture->texture_fds[i]);
			return (ft_putstr_fd("Error\nCannot open texture", 2), -1);
		}
	}
	return (0);
}

int	get_rgb_helper(t_texture *texture, char *str, char **params)
{
	char	*t;
	int		i[3];

	i[0] = -1;
	while (++i[0] < 2)
	{
		i[1] = 0;
		t = ft_strdup(ft_strnstr(str, params[i[0] + 4], ft_strlen(str)) + 2);
		if (!t)
			return (perror("Error\nAlloc failed for validating texture"), -1);
		while (t[i[1]] && t[i[1]] != ' ' && t[i[1]] != '\n')
			i[1]++;
		t[i[1]] = 0;
		i[2] = -1;
		while (t[++i[2]])
			if (t[i[2]] != ',' || (!(t[i[2]] >= '0' && t[i[2]] <= '9')))
				return (perror("Error\nRgb format invalid:"), free(t), -1);
		texture->color_fds[i[0]] = convert_rgb_to_hex(t);
		if (!texture->color_fds[i[0]])
			return (free(t), -1);
		texture->color_fds[i[0]][0] = '0';
		texture->color_fds[i[0]][1] = 'x';
		free(t);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:40:52 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/18 03:26:23 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

char	*load_map(int fd)
{
	char	*map;
	char	*t_char;
	int		single;

	map = (char *)malloc(sizeof(char) * 1);
	if (!map)
		return (printf("Allocation in load_map failed\n"), NULL);
	map[0] = 0;
	while (1)
	{
		single = 0;
		(void)read(fd, &single, 1);
		if (single < 32 && single != '\n')
			break ;
		t_char = malloc(2);
		if (!t_char)
			return (printf("Error\nAllocation t_char failed\n"), NULL);
		t_char[0] = single;
		t_char[1] = 0;
		map = str_join_block(map, t_char);
		if (!map)
			return (free(t_char), printf("Error\nstr_join alloc fail\n"), NULL);
		free(t_char);
	}
	return (map);
}

char	*copy(char *to_copy, int size)
{
	char	*new;
	int		pos;

	new = (char *)malloc(size + 1);
	if (!new)
		return (printf("Error\nAlloc failed in copy\n"), NULL);
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
		return (printf("Error\nAlloc failed in convert_rgb_to_hex\n"), NULL);
	value = (char *)malloc(9);
	if (!value)
		return (printf("Error\nAlloc failed in convert_rgb_to_hex\n"), NULL);
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
			return (printf("Error\nAlloc failed for validating texture\n"), -1);
		while (temp[walker] && temp[walker] != ' ' && temp[walker] != '\n')
			walker++;
		temp[walker] = 0;
		texture->texture_fds[i] = open(temp, O_RDONLY);
		free(temp);
	}
	return (0);
}

int	get_rgb_helper(t_texture *texture, char *str, char **params)
{
	char	*temp;
	int		i[2];

	i[0] = -1;
	while (++i[0] < 2)
	{
		i[1] = 0;
		temp = ft_strdup(ft_strnstr(str, params[i[0] + 4], ft_strlen(str)) + 2);
		if (!temp)
			return (printf("Error\nAlloc failed for validating texture\n"), -1);
		while (temp[i[1]] && temp[i[1]] != ' ' && temp[i[1]] != '\n')
			i[1]++;
		temp[i[1]] = 0;
		texture->color_fds[i[0]] = convert_rgb_to_hex(temp);
		if (!texture->color_fds[i[0]])
			return (free(temp), -1);
		texture->color_fds[i[0]][0] = '0';
		texture->color_fds[i[0]][1] = 'x';
		free(temp);
	}
	return (0);
}

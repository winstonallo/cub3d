/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:37:50 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 19:19:04 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"
#include "../../inc/constants.h"

char	**fill_params(int flag)
{
	char	**array;
	char	*arr;

	if (flag == 0)
	{
		arr = ft_strdup("NO,SO,WE,EA,F,C");
		if (!arr)
			return (perror("Error\nAllocation failed"), NULL);
	}
	else
	{
		arr = ft_strdup("North,South,West,East,Floor,Ceiling");
		if (!arr)
			return (perror("Error\nAllocation failed"), NULL);
	}
	array = ft_split(arr, ',');
	free(arr);
	if (!array)
		return (perror("Error\nAllocation failed"), NULL);
	return (array);
}

int	check_identifier(char *map, char **params, int len)
{
	int	errors;

	errors = 0;
	if (ft_strnstr(map, params[0], len))
		errors++;
	if (ft_strnstr(map, params[1], len))
		errors++;
	if (ft_strnstr(map, params[2], len))
		errors++;
	if (ft_strnstr(map, params[3], len))
		errors++;
	if (ft_strnstr(map, params[4], len))
		errors++;
	if (ft_strnstr(map, params[5], len))
		errors++;
	return (-1 + errors);
}

int	check_if_all_textures_helper(char **params, char *map, int *nl)
{
	int	line;
	int	pos;
	int	len;

	line = 0;
	pos = -1;
	while (map[++pos] && line < 6)
	{
		len = 0;
		while (map[++len])
			if (map[len] == 10)
				break ;
		if (len > 1)
		{
			if (check_identifier(map, params, len) < 0)
				return (ft_putstr_fd("Error\nTexture is missing\n", 2), -1);
			else
				line++;
		}
		*nl = *nl + 1;
		map = &map[len];
		pos = -1;
	}
	return (0);
}

int	check_for(t_check *check, char *map, char **tags, int pos)
{
	int	balancer;

	balancer = 0;
	if (pos > 3)
		balancer = 1;
	if (ft_strlen(map) < 2)
		return (ft_putendl_fd("Error\nFile content invalid", 2), -1);
	check->str = ft_strdup(
			ft_strnstr(map, tags[pos], ft_strlen(map)) + 3 - balancer);
	if (!check->str)
		return (perror("Error\nError\nAllocation failed"), -1);
	check->fd = 0;
	while (check->str[check->fd] && check->str[check->fd] != ' '
		&& check->str[check->fd] != '\n')
		check->fd++;
	if (check->str[check->fd + 1] == 32)
		if (skip_whitespaces(check->str, check->fd) == -1)
			check->change = 1;
	free(check->str);
	return (0);
}

int	check_if_rgb_correct(char *s, t_data *data, int ident)
{
	char	**rgb;
	int		correct;
	int		g;

	g = -1;
	while (s[++g])
		if (s[g] != ',' && s[g] != ' ' && (!(s[g] >= '0' && s[g] <= '9')))
			return (-1);
	correct = 0;
	if (check_before_split(s, 0, 0) < 0)
		return (-1);
	rgb = ft_split(s, ',');
	if (!rgb)
		return (perror("Error\nAllocation failed"), -1);
	if (ft_atoi(rgb[0]) >= 0 && ft_atoi(rgb[0]) < 256)
		correct++;
	if (ft_atoi(rgb[1]) >= 0 && ft_atoi(rgb[1]) < 256)
		correct++;
	if (rgb[2] && (ft_atoi(rgb[2]) >= 0 && ft_atoi(rgb[2]) < 256))
		correct++;
	if (correct == 3)
		get_color(rgb, data, ident);
	m_matrix_free(rgb);
	return (correct);
}

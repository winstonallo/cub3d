/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:37:50 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 17:49:23 by abied-ch         ###   ########.fr       */
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
			return (perror("Error\nAlloc failed in fill_params"), NULL);
	}
	else
	{
		arr = ft_strdup("North,South,West,East,Floor,Ceiling");
		if (!arr)
			return (perror("Error\nAlloc failed in fill_params"), NULL);
	}
	array = ft_split(arr, ',');
	free(arr);
	if (!array)
		return (perror("Error\nAlloc failed in fill_params_split"), NULL);
	return (array);
}

int	check_if_all_textures_helper(char **params, char **err, char *loaded_map)
{
	int	error;
	int	line;

	error = 0;
	line = 0;
	while (line < 6)
	{
		if (!ft_strnstr(loaded_map, params[line], ft_strlen(loaded_map)))
		{
			if (!error)
			{
				printf("Error\n");
				error++;
			}
			printf("%s texture is missing\n", err[line]);
		}
		line++;
	}
	return (0 - error);
}

int	check_for(t_check *check, char *map, char **tags, int pos)
{
	int	balancer;

	balancer = 0;
	if (pos > 3)
		balancer = 1;
	check->str = ft_strdup(
			ft_strnstr(map, tags[pos], ft_strlen(map)) + 3 - balancer);
	if (!check->str)
		return (perror("Error\nAlloc failed for validating texture"), -1);
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

void	get_color(char **rgb, t_data *data, int ident)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (ident == 'F')
		data->floor_color = (r << 16) | (g << 8) | b;
	else
		data->ceiling_color = (r << 16) | (g << 8) | b;
}

int	check_if_rgb_correct(char *str, t_data *data, int ident)
{
	char	**rgb;
	int		correct;
	int		g;

	g = -1;
	while (str[++g])
		if (str[g] != ',' && (!(str[g] >= '0' && str[g] <= '9')))
			return (-1);
	rgb = ft_split(str, ',');
	if (!rgb)
		return (perror("Error\nAllocation failed in check_if_rgb_correct"), -1);
	correct = 0;
	if (ft_atoi(rgb[0]) >= 0 && ft_atoi(rgb[0]) < 256)
		correct++;
	if (ft_atoi(rgb[1]) >= 0 && ft_atoi(rgb[1]) < 256)
		correct++;
	if (ft_atoi(rgb[2]) >= 0 && ft_atoi(rgb[2]) < 256)
		correct++;
	if (correct == 3)
		get_color(rgb, data, ident);
	m_matrix_free(rgb);
	return (correct);
}

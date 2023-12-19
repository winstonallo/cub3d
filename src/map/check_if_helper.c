/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:42:00 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/18 14:56:35 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

char	**fill_params(int flag)
{
	char	**array;
	char	*temp;

	array = (char **)malloc(sizeof(char *) * 7);
	if (!array)
		return (printf("Fill param allocation failed\n"), NULL);
	if (flag == 0)
	{
		temp = ft_strdup("NO,SO,WE,EA,F,C");
		if (!temp)
			return (printf("Fill param allocation failed\n"), NULL);
	}
	else
	{
		temp = ft_strdup("North,South,West,East,Floor,Ceiling");
		if (!temp)
			return (printf("Fill param allocation failed\n"), NULL);
	}
	array = ft_split(temp, ',');
	free(temp);
	if (!array)
		return (printf("Fill param allocation failed\n"), NULL);
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
		return (printf("Error\nAlloc failed for validating texture\n"), -1);
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

int	check_if_rgb_correct(char *str)
{
	char	**rgb;
	int		correct;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb)
		return (-1);
	correct = 0;
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r >= 0 && r < 256)
		correct++;
	if (g >= 0 && g < 256)
		correct++;
	if (b >= 0 && b < 256)
		correct++;
	matrix_free(rgb);
	return (correct);
}

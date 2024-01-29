/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:37:50 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 13:33:25 by abied-ch         ###   ########.fr       */
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
		pos = 0;
	}
	return (0);
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

int	count_commas(char *s)
{
	int	i;
	int	komma;

	i = -1;
	komma = 0;
	while (s[++i])
		if (s[i] == ',')
			komma++;
	return (komma);
}

int	check_code_order(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == ',' || s[i] == SPACE || !ft_isdigit(s[i]))
			break ;
	if (s[i] != ',')
		return (-1);
	if (i == 0)
		return (-1);
	return (i + 1);
}

int	check_substring(char *s, int passed, int pos, int comma)
{
	if (s[pos - 2] == SPACE)
		return (-1);
	while (s[pos] && s[pos] != '\n' && s[pos] == SPACE)
		pos++;
	while (s[pos] && s[pos] != SPACE && s[pos] != '\n' && s[pos] != ',')
		s[comma++] = s[pos++];
	if (s[pos] == SPACE && passed < 1)
		return (-1);
	if (passed > 0)
	{
		while (s[pos] && s[pos] != 10)
		{
			if (s[pos] && s[pos] != 32 && s[pos] != 10)
				return (-1);
			pos++;
		}
	}
	if (passed < 1)
		s[comma++] = ',';
	passed++;
	return (comma);
}

int	check_before_split(char *s, int pos, int passed)
{
	int	comma;
	
	if (count_commas(s) != 2)
		return (ft_putstr_fd("Error\nRGB code invalid\n", 2), -1);
	comma = check_code_order(s);
	if (comma == -1)
		return (ft_putstr_fd("Error\nRGB code invalid\n", 2), -1);
	while (s[++pos] && s[pos] != '\n' && passed < 2)
	{
		if (s[pos - 1] == ',')
		{
			comma = check_substring(s, passed, pos, comma);
			if (comma == -1)
				return (ft_putstr_fd("Error\nRGB code invalid\n", 2), -1);
		}
	}
	s[comma] = 0;
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
	if (check_before_split(s, -1, 0) < 0)
		return (correct);
	rgb = ft_split(s, ',');
	if (!rgb)
		return (perror("Error\nAllocation failed in check_if_rgb_correct"), -1);
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

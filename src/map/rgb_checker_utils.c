/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:37:33 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 19:01:19 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

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

int	check_substring(char *s, int *passed, int *p, int comma)
{
	if (s[(*p) - 2] == SPACE)
		return (-1);
	while (s[(*p)] && s[(*p)] != '\n' && s[(*p)] == SPACE)
		(*p)++;
	while (s[(*p)] && s[(*p)] != SPACE && s[(*p)] != '\n' && s[(*p)] != ',')
		s[comma++] = s[(*p)++];
	if (s[(*p)] == SPACE && *passed < 1)
		return (-1);
	if (*passed > 0)
	{
		while (s[(*p)] && s[(*p)] != 10)
		{
			if (s[(*p)] && s[(*p)] != 32 && s[(*p)] != 10)
				return (-1);
			(*p)++;
		}
	}
	if (*passed < 1)
		s[comma++] = ',';
	(*passed)++;
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
	while (s[pos] && s[pos] != '\n' && passed < 2)
	{
		if (pos > 0 && s[pos - 1] == ',')
		{
			comma = check_substring(s, &passed, &pos, comma);
			if (comma == -1)
				return (ft_putstr_fd("Error\nRGB code invalid\n", 2), -1);
		}
		pos++;
	}
	s[comma] = 0;
	return (0);
}

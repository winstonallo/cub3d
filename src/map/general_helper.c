/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:40:36 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/27 23:58:47 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"
#include "../../inc/raycast.h"
#include <stdio.h>
#include <unistd.h>

char	*str_join_block(char *str, char *str_temp)
{
	char	*temp;

	temp = ft_strjoin(str, str_temp);
	free(str_temp);
	free(str);
	if (!temp)
		return (perror("Error\nAllocation temp failed"), NULL);
	return (temp);
}

int	store_texture_path(char *str, int pos, t_data *data)
{
	if (pos == 0)
	{
		data->no_txtr = ft_strdup(str);
		if (!data->no_txtr)
			return (perror("Error\nAlloc failed"), -1);
	}
	else if (pos == 1)
	{
		data->so_txtr = ft_strdup(str);
		if (!data->so_txtr)
			return (perror("Error\nAlloc failed"), -2);
	}
	else if (pos == 2)
	{
		data->we_txtr = ft_strdup(str);
		if (!data->we_txtr)
			return (perror("Error\nAlloc failed"), -3);
	}
	else if (pos == 3)
	{
		data->ea_txtr = ft_strdup(str);
		if (!data->ea_txtr)
			return (perror("Error\nAlloc failed"), -4);
	}
	return (0);
}

int	validate_file(t_check *check, t_data *data)
{
	int	fd;
	int	err;

	fd = open(check->str, O_RDONLY);
	err = store_texture_path(check->str, check->pos, data);
	free(check->str);
	if (err < 0)
	{
		if (!(fd < 0))
			close(fd);
		return (check->valid - 1);
	}
	if (fd < 0 && check->valid == 4)
		perror("Error");
	if (fd < 0)
		return (perror("Error\ntexture path invalid"), check->valid - 1);
	close(fd);
	return (check->valid - 0);
}

int	validate_rgb(char *str, int valid, t_data *data, int ident)
{
	int	correct;
	int	index;
	int	dots;

	correct = 0;
	index = 0;
	dots = 0;
	while (index <= (int)ft_strlen(str))
	{
		if (str[index] && str[index] != ' ' && ((!(str[index] >= '0' && str[index] <= '9'))
				&& str[index] != ','))
			break ;
		if (str[index] == ',')
			dots++;
		index++;
	}
	correct = check_if_rgb_correct(str, data, ident);
	if (correct == -1)
		return (-1);
	if (dots != 2 || correct != 3)
	{
		ft_putstr_fd("Error\nRGB color code invalid\n", STDERR_FILENO);
		return (valid - 1);
	}
	return (valid);
}

int	skip_whitespaces(char *str, int pos)
{
	while (str[pos] && str[pos] == ' ')
		pos++;
	if (str[pos] == '\n')
		return (0);
	return (-1);
}

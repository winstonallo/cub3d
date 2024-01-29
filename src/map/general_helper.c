/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:40:36 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 16:37:00 by abied-ch         ###   ########.fr       */
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
	if (fd < 0)
		return (perror("Error\nTexture path invalid"), -1);
	close(fd);
	return (check->valid - 0);
}

int	validate_rgb(char *str, int valid, t_data *data, int ident)
{
	int	correct;
	int	i;
	int	dots;

	correct = 0;
	i = 0;
	dots = 0;
	while (i <= (int)ft_strlen(str))
	{
		if (str[i] && str[i] != ' ' && !ft_isdigit(str[i]) && str[i] != ',')
			break ;
		if (str[i] == ',')
			dots++;
		i++;
	}
	correct = check_if_rgb_correct(str, data, ident);
	if (correct == -1)
		return (-1);
	if (dots != 2 || correct != 3)
		return (valid - 1);
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

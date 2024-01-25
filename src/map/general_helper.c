/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:40:36 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 18:03:26 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"
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
			return (perror("Error\nAlloc failed in s_t_p"), -1);
	}
	else if (pos == 1)
	{
		data->so_txtr = ft_strdup(str);
		if (!data->so_txtr)
			return (perror("Error\nAlloc failed in s_t_p"), -2);
	}
	else if (pos == 2)
	{
		data->we_txtr = ft_strdup(str);
		if (!data->we_txtr)
			return (perror("Error\nAlloc failed in s_t_p"), -3);
	}
	else if (pos == 3)
	{
		data->ea_txtr = ft_strdup(str);
		if (!data->ea_txtr)
			return (perror("Error\nAlloc failed in s_t_p"), -4);
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
		if (err == -2)
			return (free(data->no_txtr), check->valid - 1);
		if (err == -3)
			return (free(data->no_txtr), free(data->so_txtr), check->valid - 1);
		if (err == -4)
			return (free(data->no_txtr), free(data->so_txtr),
				free(data->we_txtr), check->valid - 1);
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
		if (str[index] && ((!(str[index] >= '0' && str[index] <= '9'))
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
		ft_putstr_fd("Error\nRGB color code invalid", STDERR_FILENO);
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

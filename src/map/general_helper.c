/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:40:36 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/23 21:15:54 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

void	m_matrix_free(char **error_names)
{
	int	i;

	i = 0;
	while (error_names[i])
		free(error_names[i++]);
	free(error_names);
}

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

void	store_texture_path(char *str, int pos, t_data *data)
{
	if (pos == 0)
	{
		data->no_txtr = ft_strdup(str);
		if (!data->no_txtr)
			return (perror("Error\nAllocation failed in store_texture_path"));
	}
	else if (pos == 1)
	{
		data->so_txtr = ft_strdup(str);
		if (!data->so_txtr)
			return (perror("Error\nAllocation failed in store_texture_path"));
	}
	else if (pos == 2)
	{
		data->we_txtr = ft_strdup(str);
		if (!data->we_txtr)
			return (perror("Error\nAllocation failed in store_texture_path"));
	}
	else if (pos == 3)
	{
		data->ea_txtr = ft_strdup(str);
		if (!data->ea_txtr)
			return (perror("Error\nAllocation failed in store_texture_path"));
	}
}

int	validate_file(char *str, int valid, char **error, int pos, t_data *data)
{
	int	fd;

	fd = open(str, O_RDONLY);
	store_texture_path(str, pos, data);
	if (fd < 0 && valid == 4)
		perror("Error");
	if (fd < 0)
		return (printf("%s texture path invalid\n", error[pos]), valid - 1);
	close(fd);
	return (valid - 0);
}

int	validate_rgb(char *str, int valid, char **error, int pos)
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
	correct = check_if_rgb_correct(str);
	if (correct == -1)
		return (-1);
	if (dots != 2 || correct != 3)
		return (printf("%s RGB color code invalid\n", error[pos]), valid - 1);
	return (valid - 0);
}

int	skip_whitespaces(char *str, int pos)
{
	while (str[pos] && str[pos] == ' ')
		pos++;
	if (str[pos] == '\n')
		return (0);
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:40:36 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/21 16:58:12 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

void	matrix_free(char **error_names)
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
	char	*map;

	temp = ft_strjoin(str, str_temp);
	free(str);
	if (!temp)
		return (printf("Allocation temp failed"), NULL);
	map = ft_strjoin(temp, "");
	free(temp);
	if (!map)
		return (printf("Allocation map failed"), NULL);
	return (map);
}

int	validate_file(char *str, int valid, char **error, int pos)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0 && valid == 4)
		printf("Error\n");
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

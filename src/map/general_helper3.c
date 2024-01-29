/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_helper3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:03:04 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 13:36:38 by abied-ch         ###   ########.fr       */
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

int	skip(char *map)
{
	int	pos;

	pos = 0;
	while (map[pos] && map[pos] != ' ' && map[pos] != '\n')
		pos++;
	while (map[pos] && map[pos] == ' ')
		pos++;
	return (pos);
}

int	len(char *str)
{
	int	pos;

	pos = -1;
	while (str[++pos] && str[pos] != ' ' && str[pos] != '\n')
		;
	return (pos);
}

int	len_till_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '\n')
		;
	return (i);
}

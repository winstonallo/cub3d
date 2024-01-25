/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_public.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:42:13 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/23 18:06:19 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

int	mpl(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

int	map_get_player(int *map)
{
	int	i;

	i = 0;
	while (map[i] != -2)
	{
		if (map[i] == 'N' + 2 || map[i] == 'S' + 2
			|| map[i] == 'W' + 2 || map[i] == 'E' + 2)
			break ;
		i++;
	}
	return (i);
}

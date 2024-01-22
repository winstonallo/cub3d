/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_public.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:42:13 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/21 23:23:20 by yannis           ###   ########.fr       */
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
		if (map[i] < 100 && map[i] > 60)
			break ;
		i++;
	}
	return (i);
}

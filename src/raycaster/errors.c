/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:43:57 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 18:36:31 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	check_argument_count(int argc)
{
	if (argc < 2)
	{
		ft_putstr_fd("Error\nWrong format. Use: ./cub3d [mapnames]\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (argc > 3)
	{
		ft_putstr_fd("Error\nToo many maps (max 1)\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	free_textures(t_data *data)
{
	freeze(data->ea_txtr);
	freeze(data->we_txtr);
	freeze(data->no_txtr);
	freeze(data->so_txtr);
}

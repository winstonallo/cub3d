/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:33:56 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 15:41:47 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"
#include <stdio.h>

void	textures_init(t_data *data)
{
	get_texture_data(&data->textures.north, data, data->no_txtr);
	get_texture_data(&data->textures.south, data, data->so_txtr);
	get_texture_data(&data->textures.east, data, data->ea_txtr);
	get_texture_data(&data->textures.west, data, data->we_txtr);
}

void	set_player_angle(double *angle, char pos)
{
	if (pos == 'N')
		*angle = 3 * M_PI / 2;
	else if (pos == 'S')
		*angle = M_PI / 2;
	else if (pos == 'E')
		*angle = 0;
	else if (pos == 'W')
		*angle = M_PI;
}

void	set_player_spawn(t_data *data, int player_pos)
{
	char	pos;

	pos = data->map[player_pos] - 2;
	set_player_angle(&data->player.angle, pos);
	data->player.x_dir = cos(data->player.angle) * 5;
	data->player.y_dir = sin(data->player.angle) * 5;
	data->player.x_pos = player_pos % data->map_width + 0.45f;
	data->player.y_pos = (double)player_pos / data->map_width + 0.45f;
}

static void	mlx_pointers_init(t_data *data)
{
	data->mlx.mlx = NULL;
	data->mlx.win = NULL;
	data->mlx.img = NULL;
	data->textures.south.img = NULL;
	data->textures.north.img = NULL;
	data->textures.east.img = NULL;
	data->textures.west.img = NULL;
}

void	data_init(t_data *data)
{
	mlx_pointers_init(data);
	set_player_spawn(data, map_get_player_pos(data->map));
	set_map_scale(data);
	data->map_size = data->map_height * data->map_width;
	data->min_distance = 0;
}

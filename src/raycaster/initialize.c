/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:33:56 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/23 23:26:08 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	get_texture_data(t_txtr *t, t_data *data, char *path)
{
	t->img = mlx_xpm_file_to_image(data->mlx.mlx, path, &t->width, &t->height);
	if (t->img == NULL)
		exit_failure(data, "Error\nimage initialization failed");
	t->addr = mlx_get_data_addr(t->img, &t->bpp,&t->l_l, &t->endian);
}

void	textures_init(t_data *data)
{
	get_texture_data(&data->textures.north, data, data->no_txtr);
	get_texture_data(&data->textures.south, data, data->so_txtr);
	get_texture_data(&data->textures.east, data, data->ea_txtr);
	get_texture_data(&data->textures.west, data, data->we_txtr);
	get_texture_data(&data->textures.door, data, "src/textures/Wall5.xpm");
}

void	set_player_spawn(t_data *data, int player_pos)
{
	char	pos;

	pos = data->map[player_pos] - 2;
	if (pos == SOUTH)
		data->player.angle = PI / 2;
	else if (pos == EAST)
		data->player.angle = 0;
	else if (pos == NORTH)
		data->player.angle = 3 * PI / 2;
	else if (pos == WEST)
		data->player.angle = PI;
	data->player.x_dir = cos(data->player.angle) * 5;
	data->player.y_dir = sin(data->player.angle) * 5;
	data->player.x_pos = player_pos % data->map_width;
	data->player.y_pos = (float)player_pos / data->map_width;
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
	data->textures.door.img = NULL;
}

void	data_init(t_data *data)
{
	data->map_width = 32;  		//TODO: make dynamic
	data->map_height = 15;  	//TODO: make dynamic
	data->map_width_old = 33;  	//TODO: make dynamic
	data->map_height_old = 16; 	//TODO: make dynamic
	mlx_pointers_init(data);
	set_player_spawn(data, map_get_player_pos(data->map));
	set_wall_scaling_factor(data);
	data->map_size = data->map_height * data->map_width;
	data->min_distance = 0;
	data->elev.floor = 0;
	data->floors = 2;
	data->elev.stage = 3;
	data->elev.current = 0;
	data->elev.active = 0;
}

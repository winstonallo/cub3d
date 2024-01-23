/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:33:56 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/23 21:29:18 by abied-ch         ###   ########.fr       */
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

void	set_player_spawn(t_data *data, char pos)
{
	if (pos == 'S')
		data->player.angle = PI / 2;
	else if (pos == 'E')
		data->player.angle = 0;
	else if (pos == 'N')
		data->player.angle = 3 * PI / 2;
	else if (pos == 'W')
		data->player.angle = PI;
	data->player.x_dir = cos(data->player.angle) * 5;
	data->player.y_dir = sin(data->player.angle) * 5;
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

void	set_wall_scaling_factor(t_data *data)
{
	if (data->map_width == 3)
		data->scaling = 41.67;
	else if (data->map_width == 4)
		data->scaling = 31.25;
	else if (data->map_width == 5)
		data->scaling = 25;
	else if (data->map_width == 6)
		data->scaling = 21;
	else if (data->map_width == 7)
		data->scaling = 17.87;
	else if (data->map_width == 8)
		data->scaling = 15.62;
	else if (data->map_width == 9)
		data->scaling = 13.89;
	else if (data->map_width == 10)
		data->scaling = 12.5;
	else if (data->map_width == 11)
		data->scaling = 11.36;
	else if (data->map_width == 12)
		data->scaling = 10.42;
	else if (data->map_width == 13)
		data->scaling = 9.61;
	else if (data->map_width == 14)
		data->scaling = 8.93;
	else if (data->map_width == 15)
		data->scaling = 8.33;
	else if (data->map_width == 16)
		data->scaling = 7.81;
	else if (data->map_width == 17)
		data->scaling = 7.35;
	else if (data->map_width == 18)
		data->scaling = 6.94;
	else if (data->map_width == 19)
		data->scaling = 6.58;
	else if (data->map_width == 20)
		data->scaling = 6.25;
	else if (data->map_width == 21)
		data->scaling = 5.95;
	else if (data->map_width == 22)
		data->scaling = 5.68;
	else if (data->map_width == 23)
		data->scaling = 5.43;
	else if (data->map_width == 24)
		data->scaling = 5.21;
	else if (data->map_width == 25)
		data->scaling = 5;
	else if (data->map_width == 26)
		data->scaling = 4.81;
	else if (data->map_width == 27)
		data->scaling = 4.63;
	else if (data->map_width == 28)
		data->scaling = 4.46;
	else if (data->map_width == 29)
		data->scaling = 4.31;
	else if (data->map_width == 30)
		data->scaling = 4.17;
	else if (data->map_width == 31)
		data->scaling = 4.03;
	else if (data->map_width == 32)
		data->scaling = 3.91;
	else if (data->map_width == 33)
		data->scaling = 3.79;
	else if (data->map_width == 34)
		data->scaling = 3.68;
	else if (data->map_width == 35)
		data->scaling = 3.57;
	else if (data->map_width == 36)
		data->scaling = 3.47;
	else if (data->map_width == 37)
		data->scaling = 3.38;
	else if (data->map_width == 38)
		data->scaling = 3.29;
	else if (data->map_width == 39)
		data->scaling = 3.21;
	else if (data->map_width == 40)
		data->scaling = 3.13;
	else if (data->map_width == 41)
		data->scaling = 3.05;
	else if (data->map_width == 42)
		data->scaling = 2.98;
	else if (data->map_width == 43)
		data->scaling = 2.91;
	else if (data->map_width == 44)
		data->scaling = 2.84;
	else if (data->map_width == 45)
		data->scaling = 2.78;
	else if (data->map_width == 46)
		data->scaling = 2.72;
	else if (data->map_width == 47)
		data->scaling = 2.66;
	else if (data->map_width == 48)
		data->scaling = 2.6;
	else if (data->map_width == 49)
		data->scaling = 2.55;
	else if (data->map_width == 50)
		data->scaling = 2.5;

}

void	data_init(t_data *data, int argc)
{
	data->mlx.mlx = NULL;
	data->mlx.win = NULL;
	mlx_pointers_init(data);
	set_player_spawn(data, data->map[map_get_player_pos(data->map)] - 2);
	data->view_dir = 0;
	data->map_width = 32;  //change this
	data->map_height = 15;  //change this
	data->map_width_old = 33;  //change this
	data->map_height_old = 16; //change this
	set_wall_scaling_factor(data);
	data->x_scale = (float)SCREEN_WIDTH / 8;
	data->y_scale = (float)SCREEN_HEIGHT / 8;
	data->win_width = SCREEN_WIDTH;
	data->win_height = SCREEN_HEIGHT;
	data->line_color = 0x33ff00;
	data->map_size = data->map_height * data->map_width;
	data->min_distance = 0;
	data->player.x_pos = map_get_player_pos(data->map) % data->map_width;
	data->player.y_pos = (float)map_get_player_pos(data->map) / data->map_width;
	if (argc != 3)
		return ;
	data->player.x_oldpos = map_get_player_pos(data->maps[1]) % data->map_width;
	data->player.y_oldpos = (float)map_get_player_pos(data->maps[1]) / data->map_width;
	data->elev.floor = 0;
	data->floors = 2;
	data->elev.stage = 3;
	data->elev.current = 0;
	data->elev.active = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:33:56 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/23 20:38:42 by abied-ch         ###   ########.fr       */
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
	get_texture_data(&data->textures.wall1, data, "src/textures/pepe.xpm");
	get_texture_data(&data->textures.wall2, data, "src/textures/Wall2.xpm");
	get_texture_data(&data->textures.wall3, data, "src/textures/Wall3.xpm");
	get_texture_data(&data->textures.wall4, data, "src/textures/Wall4.xpm");
	get_texture_data(&data->textures.wall5, data, "src/textures/Wall5.xpm");
	get_texture_data(&data->textures.wall6, data, "src/textures/Wall6.xpm");
	get_texture_data(&data->textures.wall7, data, "src/textures/Wall7.xpm");
	get_texture_data(&data->textures.wall8, data, "src/textures/Wall8.xpm");
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
	data->textures.wall1.img = NULL;
	data->textures.wall2.img = NULL;
	data->textures.wall3.img = NULL;
	data->textures.wall4.img = NULL;
	data->textures.wall5.img = NULL;
	data->textures.wall6.img = NULL;
	data->textures.wall7.img = NULL;
	data->textures.wall8.img = NULL;
}

void	set_wall_scaling_factor(t_data *data)
{
	if (data->map_width == 5)
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

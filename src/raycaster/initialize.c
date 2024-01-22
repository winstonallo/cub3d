/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:33:56 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/22 18:15:00 by abied-ch         ###   ########.fr       */
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

void	data_init(t_data *data, int argc)
{
	data->mlx.mlx = NULL;
	data->mlx.win = NULL;
	mlx_pointers_init(data);
	set_player_spawn(data, data->map[map_get_player_pos(data->map)] - 2);
	data->view_dir = 0;
	data->map_width = 33;   //change this
	data->map_height = 14;  //change this
	data->map_width_old = 33;  //change this
	data->map_height_old = 16; //change this
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

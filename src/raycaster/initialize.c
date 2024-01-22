/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:33:56 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/22 15:46:57 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	get_texture_data(t_txtr *texture, t_data *data, char *texture_path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx.mlx, texture_path,
			&texture->width, &texture->height);
	if (texture->img == NULL)
		exit_failure(data, "Error\nimage initialization failed");
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->l_l, &texture->endian);
}

void	initialize_textures(t_data *data)
{
	get_texture_data(&data->textures.wall1, data, "src/textures/Wall1.xpm");
	get_texture_data(&data->textures.wall2, data, "src/textures/Wall2.xpm");
	get_texture_data(&data->textures.wall3, data, "src/textures/Wall3.xpm");
	get_texture_data(&data->textures.wall4, data, "src/textures/Wall4.xpm");
	get_texture_data(&data->textures.wall5, data, "src/textures/Wall5.xpm");
	get_texture_data(&data->textures.wall6, data, "src/textures/Wall6.xpm");
	get_texture_data(&data->textures.wall7, data, "src/textures/Wall7.xpm");
	get_texture_data(&data->textures.wall8, data, "src/textures/Wall8.xpm");
}

void	new_image(t_data *data)
{
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	data->mlx.img = mlx_new_image(data->mlx.mlx,
			data->win_width, data->win_height);
	data->img.addr = mlx_get_data_addr(data->mlx.img, &data->img.bpp,
			&data->img.l_l, &data->img.endian);
	raycast(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

void	set_player_spawn(t_data *data, char pos)
{
	if (pos == 'N')
		data->view_dir = PI / 2;
	else if (pos == 'E')
		data->view_dir = 0;
	else if (pos == 'S')
		data->view_dir = 3 * PI / 2;
	else if (pos == 'W')
		data->view_dir = PI;
	data->player.angle = data->view_dir;
	data->player.x_dir = cos(data->player.angle) * 5;
	data->player.y_dir = sin(data->player.angle) * 5;
}

void	initialize_data(t_data *data)
{
	data->mlx.mlx = NULL;
	data->mlx.win = NULL;
	data->map_width = 33;
	data->map_height = 14;
	set_player_spawn(data, data->map[map_get_player_pos(data->map)] - 2);
	data->win_width = SCREEN_WIDTH;
	data->win_height = SCREEN_HEIGHT;
	data->line_color = 0x33ff00;
	data->map_size = data->map_height * data->map_width;
	data->min_distance = 0;
	data->player.x_pos = map_get_player_pos(data->map) % data->map_width;
	data->player.y_pos = (float)map_get_player_pos(data->map) / data->map_width;
}

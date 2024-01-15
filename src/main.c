/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:49:33 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/15 21:41:44 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"

void	play_game(t_data *data)
{
	data->mlx.img = mlx_new_image(data->mlx.mlx,
			data->win_width, data->win_height);
	if (data->mlx.img == NULL)
		exit_failure(data, "Error\nimage initialization failed");
	data->img.addr = mlx_get_data_addr(data->mlx.img, &data->img.bpp,
			&data->img.l_l, &data->img.endian);
	raycast(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	mlx_hook(data->mlx.win, 2, 1L, event, data);
	mlx_hook(data->mlx.win, 17, 0, exit_success, data);
	mlx_loop(data->mlx.mlx);
}

void	get_texture_data(t_txtr *texture, t_data *data, char *texture_path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx.mlx, texture_path,
			&texture->width, &texture->height);
	if (texture->img == NULL)
		exit_failure(data, "Error\nimage initialization failed");
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->l_l, &texture->endian);
}

void	init_textures(t_data *data)
{
	get_texture_data(&data->brick, data, "src/textures/brick.xpm");
	get_texture_data(&data->stone, data, "src/textures/stone.xpm");
	get_texture_data(&data->pepe, data, "src/textures/pepe.xpm");
	get_texture_data(&data->wood, data, "src/textures/wood.xpm");
	get_texture_data(&data->grass, data, "src/textures/grass.xpm");
	get_texture_data(&data->metal, data, "src/textures/metal.xpm");
	get_texture_data(&data->walltest, data, "src/textures/walltest.xpm");
	get_texture_data(&data->wall1, data, "src/textures/Wall1.xpm");
	get_texture_data(&data->wall2, data, "src/textures/Wall2.xpm");
	get_texture_data(&data->wall3, data, "src/textures/Wall3.xpm");
	get_texture_data(&data->wall4, data, "src/textures/Wall4.xpm");
	get_texture_data(&data->wall5, data, "src/textures/Wall5.xpm");
	get_texture_data(&data->wall6, data, "src/textures/Wall6.xpm");
	get_texture_data(&data->wall7, data, "src/textures/Wall7.xpm");
	get_texture_data(&data->wall8, data, "src/textures/Wall8.xpm");
}

void	start_game(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
		exit_failure(data, "Error\nmlx initialization failed");
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->win_width,
			data->win_height, "cub3d");
	if (data->mlx.win == NULL)
		exit_failure(data, "Error\nwindow initialization failed");
	init_textures(data);
	play_game(data);
}

int	main(void)
{
	t_data	data;

	data.map = map("wow.cub");
	initialize_data(&data);
	start_game(&data);
	return (0);
}

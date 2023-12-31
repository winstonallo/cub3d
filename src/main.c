/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:49:33 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/21 14:41:01 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"

void	play_game(t_data *data)
{
	data->mlx.img = mlx_new_image(data->mlx.mlx,
			data->win_width, data->win_height);
	if (!data->mlx.img)
		exit_failure(data, "Error\nimage initialization failed");
	data->img.addr = mlx_get_data_addr(data->mlx.img, &data->img.bpp,
			&data->img.l_l, &data->img.endian);
	raycast(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	mlx_hook(data->mlx.win, 2, 1L, event, data);
	mlx_hook(data->mlx.win, 17, 0, exit_success, data);
	mlx_loop(data->mlx.mlx);
}

void	init_textures(t_data *data)
{
	data->brick.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"src/textures/brick.xpm", &data->brick.width,
			&data->brick.height);
	if (!data->brick.img)
		exit_failure(data, "Error\nimage initialization failed");
	data->brick.addr = mlx_get_data_addr(data->brick.img,
			&data->brick.bpp, &data->brick.l_l,
			&data->brick.endian);
	data->stone.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"src/textures/stone.xpm", &data->stone.width,
			&data->stone.height);
	if (!data->stone.img)
		exit_failure(data, "Error\nimage initialization failed");
	data->stone.addr = mlx_get_data_addr(data->stone.img,
			&data->stone.bpp, &data->stone.l_l,
			&data->stone.endian);
	data->pepe.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"src/textures/pepe.xpm", &data->pepe.width,
			&data->pepe.height);
	if (!data->pepe.img)
		exit_failure(data, "Error\nimage initialization failed");
	data->pepe.addr = mlx_get_data_addr(data->pepe.img,
			&data->pepe.bpp, &data->pepe.l_l,
			&data->pepe.endian);
}

void	start_game(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		exit_failure(data, "Error\nmlx initialization failed");
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->win_width,
			data->win_height, "cub3d");
	if (!data->mlx.win)
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

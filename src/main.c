/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:49:33 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/17 22:59:40 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"
#include <mlx.h>
#include <stdlib.h>

int map[]=
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,1,0,1,
	1,0,0,1,1,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,0,0,0,'N',1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

void	play_game(t_data *data)
{
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->win_width, data->win_height);
	if (!data->mlx.img)
		exit_failure(data, "Error\nimage initialization failed");
	data->img.addr = mlx_get_data_addr(data->mlx.img, &data->img.bpp, &data->img.l_l, &data->img.endian);
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
			put_pixel(data, i, j, 0xE4F6F8);
	}
	raycast(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	mlx_hook(data->mlx.win, 2, 1L, event, data);
	mlx_hook(data->mlx.win, 17, 0, exit_success, data);
	mlx_loop(data->mlx.mlx);
}

void start_game(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		exit_failure(data, "Error\nmlx initialization failed");
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->win_width, data->win_height, "cub3d");
	if (!data->mlx.win)
		exit_failure(data, "Error\nwindow initialization failed");

	play_game(data);
}

int	main(void)
{
	t_data	data;


	data.map = map;
	initialize_data(&data);
	set_data_view(&data);
	start_game(&data);
	return (0);
}

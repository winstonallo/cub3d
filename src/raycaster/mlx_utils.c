/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:22 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/16 12:26:46 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

static void	play_game(t_data *data)
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

void	start_game(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
		exit_failure(data, "Error\nmlx initialization failed");
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->win_width,
			data->win_height, "cub3d");
	if (data->mlx.win == NULL)
		exit_failure(data, "Error\nwindow initialization failed");
	initialize_textures(data);
	play_game(data);
}

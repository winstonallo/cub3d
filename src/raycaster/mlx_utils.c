/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:22 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/22 18:17:57 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"
#include <stdio.h>

int	loop(void *data)
{
	t_data	*game;

	game = (t_data *)data;
	// mlx_clear_window(game->mlx.mlx, game->mlx.win);
	
	gif_loop(game);
	// pre_render(game);
	// button_loop(game);
	return (0);
}

static void	play_game(t_data *data)
{
	data->mlx.img = mlx_new_image(data->mlx.mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (data->mlx.img == NULL)
		exit_failure(data, "Error\nimage initialization failed");
	data->img.addr = mlx_get_data_addr(data->mlx.img, &data->img.bpp,
			&data->img.l_l, &data->img.endian);
	textures_init(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	mlx_loop_hook(data->mlx.mlx, loop, data);
	mlx_hook(data->mlx.win, 2, 1L, event, data);
	mlx_hook(data->mlx.win, 17, 0, exit_success, data);
	mlx_loop(data->mlx.mlx);
}

void	start_game_f_b_g(t_data *data)
{
	data->font = font_init(data->mlx.mlx);
	if (!data->font)
		exit_failure(data, "Error\nfont initialization failed");
	data->gifs = 0;
	if (gif_init(data, "src/mlx_gif/gifs/rick/frame", -800, -800) < 0)
		exit_failure(data, "Error\nfont initialization failed");
	if (gif_init(data, "src/mlx_gif/gifs/bongo/frame", -800, -800) < 0)
		exit_failure(data, "Error\nfont initialization failed");
}

void	start_game(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
		exit_failure(data, "Error\nmlx initialization failed");
	data->mlx.win = mlx_new_window(data->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"cub3d");
	if (data->mlx.win == NULL)
		exit_failure(data, "Error\nwindow initialization failed");
	start_game_f_b_g(data);
	play_game(data);
}

void	new_image(t_data *data)
{
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	data->mlx.img = mlx_new_image(data->mlx.mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->mlx.img, &data->img.bpp,
			&data->img.l_l, &data->img.endian);
	raycast(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

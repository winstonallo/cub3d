/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:11:33 by yannis            #+#    #+#             */
/*   Updated: 2024/01/18 03:29:25 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/raycast.h"

void	free_game(t_data *game)
{
	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	mlx_destroy_display(game->mlx.mlx);
	free(game->mlx.mlx);
	free(game);
}

void	pre_render(t_data *game)
{
	int				pos;

	pos = -1;
	while (++pos < game->button_index)
	{
		if (game->button[pos]->activate == 1 && game->button[pos]->active == 0)
			mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->button[pos]->img[0].img, game->button[pos]->posx, game->button[pos]->posy);
	}
}

int	loop(void *data)
{
	t_data	*game;

	game = (t_data *)data;
	mlx_clear_window(game->mlx.mlx, game->mlx.win);
	gif_loop(game);
	pre_render(game);
	button_loop(game);
	return (0);
}

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
	mlx_loop_hook(data->mlx.mlx, loop, data);
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

int	init_fonts(t_data *game)
{
	game->font = font_init(game->mlx.mlx);
	if (!game->font)
		return (perror("Error:\n"),
			mlx_destroy_window(game->mlx.mlx, game->mlx.win),
			mlx_destroy_display(game->mlx.mlx), free(game->mlx.mlx), free(game), 1);
	game->gifs = 0;
	if (gif_init(game, "src/mlx_gif/gifs/elevator-right/up/frame", 100, 100) < 0)
		return (free_game(game), 1);
	if (gif_init(game, "src/mlx_gif/gifs/elevator-right/down/frame", 1164, 100) < 0)
		return (free_game(game), 1);
	if (gif_init(game, "src/mlx_gif/gifs/elevator_back/up/frame", 164, 100) < 0)
		return (free_game(game), 1);
	return (0);
}

void	start_games(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		exit_failure(data, "Error\nmlx initialization failed");
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->win_width,
			data->win_height, "cub3d");
	if (!data->mlx.win)
		exit_failure(data, "Error\nwindow initialization failed");
	init_textures(data);
	if (init_fonts(data) < 0)
		exit_failure(data, "Error\nfont initialization failed");
	play_game(data);
}

int	main(void)
{
	t_data	data;

	data.map = map("wow.cub");
	initialize_data(&data);
	start_games(&data);
	return (0);
}

// int	main()
// {
	

// 	// Überarbeiten der button initialisierung. vorbild an gif initialisierung nehmen
// 	game->button_index = 0;
// 	game->clicked = 0;
// 	if (button_init(game, "src/button/button_textures/wall/wall", int_exit) < 0)
// 		return (free_game(game), -1);
// 	if (button_init(game, "src/button/button_textures/test/test", say) < 0)
// 		return (button_delete(game, game->mlx), free(game->button), free_game(game), -1);
// 	if (button_init(game, "src/button/button_textures/test/test", say) < 0)
// 		return (button_delete(game, game->mlx), free(game->button), free_game(game), -1);
// 	if (button_init(game, "src/button/button_textures/wall/wall", second_win) < 0)
// 		return (button_delete(game, game->mlx), free(game->button), free_game(game), -1);
// 	button_change_position(game, 100, 200, 0);
// 	button_change_position(game, 200, 200, 1);
// 	button_change_position(game, 300, 200, 2);
// 	button_change_position(game, 400, 200, 3);

// 	// img.img = mlx_xpm_file_to_image(game->mlx, "src/font/fonts/test.xpm", &img.width, &img.height);
// 	// fs = font_settings(0, 200, WHITE, 3);
// 	// font_write_img("Hello World", game, &img, fs);
// 	// mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
// 	// fs = font_settings(100, 100, BROWN, 4);
// 	// font_write("Test color\n", game, fs);
// 	// fs = font_settings(700, 300, BLUE, 2);
// 	// font_write("Cool shit\n", game, fs);
// 	mlx_mouse_hook(game->win, mouse_hook, game);
// 	mlx_hook(game->win, 2, 1L, test, NULL);
// 	mlx_loop(game->mlx);
// 	button_delete(game, game->mlx);
// 	free_game(game);
// }



int	g_test = 0;
int	g_end = 0;

int	mouse_hook(int button, int x, int y, t_data *temp)
{
	(void)button;
	int	i;

	i = 0;
	if (button == 1 && g_test == 0)
	{
		while (i < temp->button_index)
		{
			if ((x >= temp->button[i]->posx
				&& x <= temp->button[i]->posx + temp->button[i]->img->width)
				&& (y >= temp->button[i]->posy
				&& y <= temp->button[i]->posy + temp->button[i]->img->height))
			{
				temp->button[i]->button_clicked = 1;
				temp->clicked = 1;
			}
			i++;
		}
	}
	else if (button == 1)
		g_end = 1;
	return (0);
}

int	test()
{
	write(1, "Lol\n", 4);
	return (0);
}

int	second_win(t_data *game, int i)
{
	t_font_setting	font_setting;

	(void)i;
	font_setting = font_settings(200, 100, WHITE, 4);
	while (1)
	{
		font_write("Inside", game, font_setting);
		if (g_end == 1)
			break;
	}
	return (0);
}

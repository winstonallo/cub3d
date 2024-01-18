<<<<<<< HEAD
#include "cub3d.h"

void	free_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
}

void	pre_render(t_game *game)
{
	// t_font_setting	fs;
	int				pos;

	pos = -1;
	while (++pos < game->button_index)
	{
		if (game->button[pos]->activate == 1 && game->button[pos]->active == 0)
			mlx_put_image_to_window(game->mlx, game->win, game->button[pos]->img[0].img, game->button[pos]->posx, game->button[pos]->posy);
	}
	// fs = font_settings(0, 0, WHITE, 3);
	// font_write_img("Hello World", game, game->gif[0]->display, fs);
	// fs = font_settings(100, 100, BROWN, 4);
	// font_write("Test color", game, fs);
	// fs = font_settings(700, 300, BLUE, 2);
	// font_write("Cool shit", game, fs);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:49:33 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/16 12:19:47 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"
>>>>>>> 27408219654e99af46da574da2fa7074fbfb7d4e

int	loop(void *data)
{
	t_game	*game;

<<<<<<< HEAD
	game = (t_game *)data;
	mlx_clear_window(game->mlx, game->win);
	gif_loop(game);
	pre_render(game);
	button_loop(game);
=======
	data.map = map("wow.cub");
	initialize_data(&data);
	start_game(&data);
>>>>>>> 27408219654e99af46da574da2fa7074fbfb7d4e
	return (0);
}

int	g_test = 0;
int	g_end = 0;

int	mouse_hook(int button, int x, int y, t_game *temp)
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

int	second_win(t_game *game, int i)
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

int	main()
{
	// t_texture	txts;
	// int			*game;
	// t_font_setting	fs;
	// t_game			*game;
	t_game			*game;
	// t_img			img;
	// t_img			img2;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (perror("Error\n"), 1);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free(game), perror("Error\n"), 1);
	game->win = mlx_new_window(game->mlx, 1500, 1000, "Test");
	if (!game->win)
		return (free(game->mlx), free(game), perror("Error\n"), 1);
	game->font = font_init(game->mlx);
	// game->font = NULL;
	if (!game->font)
		return (perror("Error:\n"), mlx_destroy_window(game->mlx, game->win), mlx_destroy_display(game->mlx), free(game->mlx), free(game), 1);
	game->gifs = 0;
	if (gif_init(game, "src/mlx_gif/gifs/elevator-right/up/frame", 100, 100) < 0)
		return (free_game(game), perror("Error\n"), 1);
	if (gif_init(game, "src/mlx_gif/gifs/elevator-right/down/frame", 1164, 100) < 0)
		return (free_game(game), perror("Error\n"), 1);
	if (gif_init(game, "src/mlx_gif/gifs/elevator_back/up/frame", 164, 100) < 0)

	// Überarbeiten der button initialisierung. vorbild an gif initialisierung nehmen
	game->button_index = 0;
	game->clicked = 0;
	if (button_init(game, "src/button/button_textures/wall/wall", int_exit) < 0)
		return (free_game(game), -1);
	if (button_init(game, "src/button/button_textures/test/test", say) < 0)
		return (button_delete(game, game->mlx), free(game->button), free_game(game), -1);
	if (button_init(game, "src/button/button_textures/test/test", say) < 0)
		return (button_delete(game, game->mlx), free(game->button), free_game(game), -1);
	if (button_init(game, "src/button/button_textures/wall/wall", second_win) < 0)
		return (button_delete(game, game->mlx), free(game->button), free_game(game), -1);
	button_change_position(game, 100, 200, 0);
	button_change_position(game, 200, 200, 1);
	button_change_position(game, 300, 200, 2);
	button_change_position(game, 400, 200, 3);

	// img.img = mlx_xpm_file_to_image(game->mlx, "src/font/fonts/test.xpm", &img.width, &img.height);
	// fs = font_settings(0, 200, WHITE, 3);
	// font_write_img("Hello World", game, &img, fs);
	// mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
	// fs = font_settings(100, 100, BROWN, 4);
	// font_write("Test color\n", game, fs);
	// fs = font_settings(700, 300, BLUE, 2);
	// font_write("Cool shit\n", game, fs);
	mlx_mouse_hook(game->win, mouse_hook, game);
	mlx_loop_hook(game->mlx, loop, game);
	mlx_hook(game->win, 2, 1L, test, NULL);
	mlx_loop(game->mlx);
	button_delete(game, game->mlx);
	free_game(game);
}
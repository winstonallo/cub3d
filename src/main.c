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
	int	pos;

	pos = -1;
	while (++pos < game->button_index)
	{
		if (game->button[pos]->activate == 1 && game->button[pos]->active == 0)
			mlx_put_image_to_window(game->mlx, game->win, game->button[pos]->img[0].img, game->button[pos]->posx, game->button[pos]->posy);
	}
}

int	loop(void *data)
{
	t_game	*game;

	game = (t_game *)data;
	mlx_clear_window(game->mlx, game->win);
	gif_loop(game);
	pre_render(game);
	button_loop(game);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_game *temp)
{
	(void)button;
	int	i;

	i = 0;
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
	return (0);
}

int	test()
{
	write(1, "Lol\n", 4);
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

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (perror("Error\n"), 1);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free(game), perror("Error\n"), 1);
	game->win = mlx_new_window(game->mlx, 1500, 1000, "Test");
	if (!game->win)
		return (free(game->mlx), free(game), perror("Error\n"), 1);
	game->gifs = 0;
	if (gif_init(game, "src/mlx_gif/gifs/rick/frame", 100, 100) < 0)
		return (free_game(game), perror("Error\n"), 1);
	if (gif_init(game, "src/mlx_gif/gifs/bongo/frame", 550, 100) < 0)
		return (free_game(game), perror("Error\n"), 1);

	// Überarbeiten der button initialisierung. vorbild an gif initialisierung nehmen
	game->button_index = 0;
	game->clicked = 0;
	if (button_init(game, "src/button/button_textures/wall/wall", int_exit) < 0)
		return (free_game(game), -1);
	if (button_init(game, "src/button/button_textures/test/test", say) < 0)
		return (button_delete(game, game->mlx), free(game->button), free_game(game), -1);
	if (button_init(game, "src/button/button_textures/test/test", say) < 0)
		return (button_delete(game, game->mlx), free(game->button), free_game(game), -1);
	if (button_init(game, "src/button/button_textures/wall/wall", say) < 0)
		return (button_delete(game, game->mlx), free(game->button), free_game(game), -1);
	button_change_position(game, 100, 200, 0);
	button_change_position(game, 200, 200, 1);
	button_change_position(game, 300, 200, 2);
	button_change_position(game, 400, 200, 3);

	mlx_mouse_hook(game->win, mouse_hook, game);
	mlx_loop_hook(game->mlx, loop, game);
	mlx_hook(game->win, 2, 1L, test, NULL);
	mlx_loop(game->mlx);
	gif_delete(game, game->mlx);
	button_delete(game, game->mlx);
	free_game(game);
}
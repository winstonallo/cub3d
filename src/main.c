#include "cub3d.h"

void	free_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
}

int mouse_hook(void *data)
{
	t_game *game;
	int gif;
	double elapsed_time;
	static struct timespec start_time;
	struct timespec current_time;

	game = (t_game *)data;
	gif = -1;
	mlx_clear_window(game->mlx, game->win);
	while (++gif < game->gifs)
		mlx_put_image_to_window(game->mlx, game->win, game->gif[gif]->img[game->gif[gif]->curr].img, game->gif[gif]->posx, game->gif[gif]->posy);
	if (start_time.tv_sec == 0 && start_time.tv_nsec == 0)
		clock_gettime(CLOCK_REALTIME, &start_time);
	else
	{
		clock_gettime(CLOCK_REALTIME, &current_time);
		elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000.0;
		elapsed_time += (current_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
		if (elapsed_time >= 37)
		{
			gif = -1;
			while (++gif < game->gifs)
			{
				game->gif[gif]->curr++;
				if (game->gif[gif]->curr == game->gif[gif]->del)
					game->gif[gif]->curr = 0;
			}
			clock_gettime(CLOCK_REALTIME, &start_time);
		}
	}
	return (0);
}

int	test()
{
	write(1, "Lol\n", 4);
	return (0);
}

int main()
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
	if (gif_init(game, "src/mlx_gif/gifs/bongo/frame", 700, 100) < 0)
		return (free_game(game), perror("Error\n"), 1);
	printf("Gifs: %i\n", game->gifs);
	mlx_loop_hook(game->mlx, mouse_hook, game);
	mlx_hook(game->win, 2, 1L, test, NULL);
	// mlx_loop(game->mlx);
	gif_delete(game, game->mlx);
	free_game(game);
}
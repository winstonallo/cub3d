#include "cub3d.h"

int	gif_loop(t_game *game);

void	free_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
}

int	loop(void *data)
{
	t_game	*game;

	game = (t_game *)data;
	mlx_clear_window(game->mlx, game->win);
	gif_loop(game);
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
	mlx_loop_hook(game->mlx, loop, game);
	mlx_hook(game->win, 2, 1L, test, NULL);
	mlx_loop(game->mlx);
	gif_delete(game, game->mlx);
	free_game(game);
}
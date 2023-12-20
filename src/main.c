#include "cub3d.h"

void	free_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
}

void	destroy(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
}

int main()
{

	// t_texture	txts;
	// int			*game;
	t_font_setting	fs;
	t_game			*game;
	t_img			img;

	game = (t_game *)malloc(sizeof(t_game));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1260, 720, "Test");
	game->font = font_init(game->mlx);
	if (!game->font)
		return (destroy(game), -1);
	write(1, "font finished\n", 14);
	img.img = mlx_xpm_file_to_image(game->mlx, "src/font/fonts/test.xpm", &img.width, &img.height);
	// game = map("wow.cub");
	// if (!game)
	// 	return (free(game), 1);
	// // printf("Playerpos: %i\n", map_get_player_pos(game));
	// txts = map_get_textures("wow.cub");
	// if (txts.err_code != 0)
	// 	return (1);
	// // printf("%i\n", txts.texture_fds[1]);
	// free(txts.color_fds[0]);
	// free(txts.color_fds[1]);
	// free(game);

	fs = font_settings(10, 10, 0x00FFFFFF, 4);
	font_write("Hello world", game, &img, fs);
	fs = font_settings(10, 100, 0x0000FFFF, 3);
	font_write("Hello world", game, &img, fs);
	fs = font_settings(10, 160, DARK_AQUA, 2);
	font_write("Hello world", game, &img, fs);
	fs = font_settings(10, 210, 0x00FFFF00, 1);
	font_write("Hello world", game, &img, fs);
	mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
	mlx_loop(game->mlx);
	mlx_destroy_image(game->mlx, img.img);
	font_delete(game);
	free_game(game);
	return (0);
}
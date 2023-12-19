// #include "cub3d.h"
#include "font/font.h"

void	free_game(t_game *game)
{
	int	letter;

	letter = 0;
	while (letter < 26)
	{
		mlx_destroy_image(game->mlx, game->font->xl_font.letter[letter].img);
		mlx_destroy_image(game->mlx, game->font->big_font.letter[letter].img);
		mlx_destroy_image(game->mlx,
							game->font->medium_font.letter[letter].img);
		mlx_destroy_image(game->mlx, game->font->small_font.letter[letter].img);
		letter++;
	}
	free(game->font->xl_font.letter);
	free(game->font->big_font.letter);
	free(game->font->medium_font.letter);
	free(game->font->small_font.letter);
	free(game->font);
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
	t_game	*game;
	t_img	img;

	game = (t_game *)malloc(sizeof(t_game));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1260, 720, "Test");
	game->font = font_init(game->mlx);
	if (!game->font)
		return (destroy(game), -1);
	write(1, "font finished\n", 13);
	game->cords.img_x = 10;
	game->cords.img_y = 10;
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
	font_write("Hello world", game, &img, 4);
	game->cords.img_x = 10;
	game->cords.img_y = 100;
	font_write("Hello world", game, &img, 3);
	game->cords.img_x = 10;
	game->cords.img_y = 160;
	font_write("Hello world", game, &img, 2);
	game->cords.img_x = 10;
	game->cords.img_y = 210;
	font_write("Hello world", game, &img, 1);
	mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
	mlx_loop(game->mlx);
	mlx_destroy_image(game->mlx, img.img);
	free_game(game);
	return (0);
}
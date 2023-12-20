#include "cub3d.h"
#include "button/button.h"

void	free_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
}

int mouse_hook(int button, int x, int y, t_temp *temp)
{
	(void)button;
	if ((x >= 100 && x <= 140) && (y >= 100 && y <= 140))
		temp->buttonclicked = 1;
	return (0);
}

int main()
{

	// t_texture	txts;
	// int			*game;
	// t_font_setting	fs;
	// t_game			*game;
	t_temp			*game;
	t_button		*button;
	// t_img			img;

	game = (t_temp *)malloc(sizeof(t_temp));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1260, 720, "Test");
	button = button_init(game->mlx, "src/button/");
	game->button = button;
	game->buttonclicked = 0;
	mlx_put_image_to_window(game->mlx, game->win, game->button->img[0].img, 100, 100);
	mlx_mouse_hook(game->win, mouse_hook, game);
	mlx_loop_hook(game->mlx, click, game);
	mlx_loop(game->mlx);
	// free_game(game);
}
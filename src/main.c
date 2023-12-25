#include "cub3d.h"
#include "button/button.h"

void	free_game(t_temp *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
}

int mouse_hook(int button, int x, int y, t_temp *temp)
{
	(void)button;
	int	i;

	i = 0;
	while (i < temp->button_index)
	{
		if ((x >= temp->button[i]->posx && x <= temp->button[i]->posx + 40)
			&& (y >= temp->button[i]->posy && y <= temp->button[i]->posy + 40))
		{
			temp->button[i]->button_clicked = 1;
			temp->clicked = 1;
		}
		i++;
	}
	return (0);
}

int main()
{

	// t_texture	txts;
	// int			*game;
	// t_font_setting	fs;
	// t_game			*game;
	t_temp			*game;
	// t_img			img;

	game = (t_temp *)malloc(sizeof(t_temp));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1260, 720, "Test");
	game->button = (t_button **)malloc(sizeof(t_button *) * 2);
	game->button_index = 0;
	game->clicked = 0;
	game->button[0] = button_init(game->mlx, "src/button/button_textures/wall/wall");
	if (!game->button[0])
		return (free(game->button), free_game(game), -1);
	game->button[1] = button_init(game->mlx, "src/button/button_textures/test/test");
	if (!game->button[1])
		return (button_delete(game->button[0], game->mlx), free(game->button), free_game(game), -1);
	game->button_index++;
	game->button_index++;
	game->button[0]->activate = 1;
	button_add_function(int_exit, game, 0);
	button_add_function(say, game, 1);
	button_change_position(game, 100, 100, 0);
	button_change_position(game, 200, 200, 1);
	mlx_mouse_hook(game->win, mouse_hook, game);
	mlx_loop_hook(game->mlx, button_animation, game);
	mlx_loop(game->mlx);
	button_delete(game->button[0], game->mlx);
	button_delete(game->button[1], game->mlx);
	free(game->button);
	free_game(game);
}
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

int	test(void *data)
{
	static	int	inc;
	static	int	lap;
	static	int	active;
	static	int	i;
	int			second;
	t_temp		*game;

	game = data;
	if (game->clicked == 0)
		return (0);
	while (inc == 0 && i < game->button_index)
	{
		if (game->button[i]->button_clicked == 1)
		{
			active = 1;
			break ;
		}
		i++;
	}
	if (active == 0)
		return (0);
	mlx_clear_window(game->mlx, game->win);
	second = 0;
	while (second < game->button_index)
	{
		if (i != second)
			mlx_put_image_to_window(game->mlx, game->win, game->button[second]->img[0].img, game->button[second]->posx, game->button[second]->posy);
		second++;
	}
	if (inc < 9)
		mlx_put_image_to_window(game->mlx, game->win, game->button[i]->img[inc].img, game->button[i]->posx + inc, game->button[i]->posy + inc);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->button[i]->img[8 - lap].img, game->button[i]->posx + 8 - lap, game->button[i]->posy + 8 - lap);
	if (inc == 17)
	{
		active = 0;
		lap = 0;
		inc = 0;
		if (i == 0)
			exit(0);
		i = 0;
		game->button[i]->button_clicked = 0;
		game->clicked = 0;
		return (0);
	}
	usleep(4242);
	if (inc > 8)
		lap++;
	inc++;
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
	game->button[0] = button_init(game->mlx, "src/button/");
	game->button[1] = button_init(game->mlx, "src/button/");
	game->button_index++;
	game->button_index++;
	game->button[0]->iden = 0;
	game->button[1]->iden = 1;
	game->button[0]->posx = 100;
	game->button[0]->posy = 100;
	game->button[1]->posx = 200;
	game->button[1]->posy = 200;
	game->button[0]->button_clicked = 0;
	game->button[1]->button_clicked = 0;
	mlx_put_image_to_window(game->mlx, game->win, game->button[0]->img[0].img, 100, 100);
	mlx_put_image_to_window(game->mlx, game->win, game->button[1]->img[0].img, 200, 200);
	mlx_mouse_hook(game->win, mouse_hook, game);
	mlx_loop_hook(game->mlx, test, game);
	mlx_loop(game->mlx);
	// free_game(game);
}
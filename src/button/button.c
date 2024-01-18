/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:43:31 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/18 01:47:18 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/button.h"

void	b_matrix_free(char **arr)
{
	int	pos;

	pos = 0;
	while (arr[pos])
		free(arr[pos++]);
	free(arr);
}
int	button_loop_check(t_game *game, t_button_loop *loop)
{
	if (game->clicked == 0)
		return (0);
	while (loop->inc == 0 && loop->i < game->button_index)
	{
		if (game->button[loop->i]->button_clicked == 1)
		{
			loop->active = 1;
			game->button[loop->i]->active = 1;
			break ;
		}
		loop->i++;
	}
	if (loop->active == 0)
		return (0);
	return (1);
}

int	button_loop_elapsed_time(t_game *game, t_button_loop *loop)
{
	if (loop->inc > 8)
		loop->lap++;
	loop->inc++;
	if (loop->inc == 17)
	{
		loop->active = 0;
		game->button[loop->i]->active = 0;
		loop->lap = 0;
		loop->inc = 0;
		if (!(game == NULL || game->button[loop->i] == NULL
			|| game->button[loop->i]->function == NULL))
			if (game->button[loop->i]->button_clicked == 1
				&& game->button[loop->i]->activate == 1)
				loop->status = mouse_actions(game->button[loop->i]->function,
					game, loop->i);
		game->button[loop->i]->button_clicked = 0;
		loop->i = 0;
		game->clicked = 0;
	}
	clock_gettime(CLOCK_REALTIME, &loop->start_time);
	return (loop->status);
}

int	button_loop(t_game *game)
{
	static	t_button_loop	loop;

	if (button_loop_check(game, &loop) == 0)
		return (0);
	loop.status = 0;
	display_button(game, loop.i, loop.lap, loop.inc);
	if (loop.start_time.tv_sec == 0 && loop.start_time.tv_nsec == 0)
		clock_gettime(CLOCK_REALTIME, &loop.start_time);
	else
	{
		clock_gettime(CLOCK_REALTIME, &loop.current_time);
		loop.elapsed_time = (loop.current_time.tv_sec - loop.start_time.tv_sec) * 1000.0;
		loop.elapsed_time += (loop.current_time.tv_nsec - loop.start_time.tv_nsec) / 1000000.0;
		if (loop.elapsed_time >= 3)
			return (button_loop_elapsed_time(game, &loop));
	}
	return (loop.status);
}

t_button	**transfer_buttons(t_game *game)
{
	t_button	**buttons;
	int			i;

	buttons = (t_button **)malloc(sizeof(t_button *) * (game->button_index + 1));
	if (!buttons)
		return (perror("Error\n"), NULL);
	i = -1;
	while (++i < game->button_index)
		buttons[i] = game->button[i];
	free(game->button);
	return (buttons);
}

t_button	*button_init_single(void *mlx, char *path, int (*f)(t_game *, int))
{
	t_button	*button;

	button = (t_button *)malloc(sizeof(t_button));
	if (!button)
		return (perror("Error\n"), NULL);
	button->activate = 0;
	button->img = (t_img *)malloc(sizeof(t_img) * 9);
	if (!button->img)
		return (free(button), perror("Error\n"), NULL);
	if (load_button(button, mlx, path) < 0)
		return (free(button->img), free(button), perror("Error\n"), NULL);
	button->curr = 0;
	button->activate = 1;
	button->active = 0;
	button->function = f;
	return (button);
}

void	button_delete_master(t_game *game, void *mlx)
{
	int	inner;
	int	pos;

	inner = -1;
	while (++inner < game->button_index)
	{
		pos = -1;
		while (++pos < game->button[inner]->del)
			mlx_destroy_image(mlx, game->button[inner]->img[pos].img);
		free(game->button[inner]->img);
		free(game->button[inner]);
	}
	free(game->button);
}

int	button_init_master(t_game *game, char *path, int (*f)(t_game *, int))
{
	t_button	**buttons;
	t_button	*button;
	static	int	button_pos;

	if (button_pos == 0)
	{
		buttons = (t_button **)malloc(sizeof(t_button *));
		if (!buttons)
			return (perror("Error\n"), -1);
	}
	else
	{
		buttons = transfer_buttons(game);
		if (!buttons)
			return (button_delete_master(game, game->mlx), perror("Error\n"), -1);
	}
	button = button_init_single(game->mlx, path, f);
	if (!button)
		return (button_delete_master(game, game->mlx), perror("Error\n"), -1);
	buttons[button_pos] = button;
	button_pos++;
	game->button_index = button_pos;
	game->button = buttons;
	return (0);
}

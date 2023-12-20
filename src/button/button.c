/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:43:31 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/20 23:46:12 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

void	matrix_free(char **arr)
{
	int	pos;

	pos = 0;
	while (arr[pos])
		free(arr[pos++]);
	free(arr);
}

t_button	*button_init(void *mlx, char *path)
{
	t_button	*button;

	button = (t_button *)malloc(sizeof(t_button));
	if (!button)
		return (perror("Error\n"), NULL);
	button->img = (t_img *)malloc(sizeof(t_img) * 9);
	load_button(button, mlx, path);
	return (button);
}

int	click(void *temp)
{
	int	i;
	t_temp *game;

	i = 0;
	game = (t_temp *)temp;
	if (game->buttonclicked == 0)
		return (0);
	while (i < game->button->del - 1)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_put_image_to_window(game->mlx, game->win, game->button->img[i].img, 100 + i, 100 + i);
		i++;
	}
	while (i >= 0)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_put_image_to_window(game->mlx, game->win, game->button->img[i].img, 100 + i, 100 + i);
		i--;
	}
	game->buttonclicked = 0;
	return (0);
}

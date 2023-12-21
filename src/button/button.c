/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:43:31 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/21 13:56:08 by yatabay          ###   ########.fr       */
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

int	click(void *data)
{
	t_temp	*game;
	int		i;

	i = 0;
	game = (t_temp *)data;
	while (i < game->button[0]->del - 1)
	{
		// mlx_clear_window(game->mlx, game->win);
		// mlx_put_image_to_window(game->mlx, game->win, game->button->img[i].img, 100 + (i * 40), 100 + i);
		// usleep(100000);
		write(1, "test\n", 5);
		i++;
	}
	// while (i >= 0)
	// {
	// 	mlx_clear_window(game->mlx, game->win);
	// 	mlx_put_image_to_window(game->mlx, game->win, game->button->img[i].img, 100 + i, 100 + i);
	// 	i--;
	// }
	return (0);
}

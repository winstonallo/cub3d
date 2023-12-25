/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:43:31 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/26 00:06:40 by yannis           ###   ########.fr       */
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

t_button	*button_init_master(void *mlx, char *path)
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
	return (button);
}

void	button_delete_master(t_button *button, void *mlx)
{
	int	pos;

	pos = -1;
	while (++pos < button->del)
		mlx_destroy_image(mlx, button->img[pos].img);
	free(button->img);
	free(button);
}

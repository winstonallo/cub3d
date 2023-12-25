/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_public.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:13:25 by yannis            #+#    #+#             */
/*   Updated: 2023/12/25 23:24:23 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_button	*button_init_master(void *mlx, char *path);
void		button_delete_master(t_button *button, void *mlx);
int			button_add_function_master(int (*function)(t_game *, int i), t_game *game, int i);
int			button_change_position_master(t_game *game, int posx, int posy, int iden);


t_button	*button_init(void *mlx, char *path)
{
	return (button_init_master(mlx, path));
}

void	button_delete(t_button *button, void *mlx)
{
	button_delete_master(button, mlx);
}

int	button_add_function(int (*function)(t_game *, int i), t_game *game, int i)
{
	return (button_add_function_master(function, game, i));
}

int	button_change_position(t_game *game, int posx, int posy, int iden)
{
	return (button_change_position_master(game, posx, posy, iden));
}
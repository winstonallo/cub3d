/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_public.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:13:25 by yannis            #+#    #+#             */
/*   Updated: 2024/01/18 02:38:47 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

int			*button_init_master(t_data *game, char *path, int (*f)(t_data *, int));
void		button_delete_master(t_data *game, void *mlx);
int			button_add_function_master(int (*function)(t_data *, int i), t_data *game, int i);
int			button_change_position_master(t_data *game, int posx, int posy, int iden);
int			button_switch_master(t_data *game, int i);

int	*button_init(t_data *game, char *path, int (*f)(t_data *, int))
{
	return (button_init_master(game, path, f));
}

void	button_delete(t_data *game, void *mlx)
{
	button_delete_master(game, mlx);
}

int	button_change_function(int (*function)(t_data *, int i), t_data *game, int i)
{
	return (button_add_function_master(function, game, i));
}

int	button_change_position(t_data *game, int posx, int posy, int iden)
{
	return (button_change_position_master(game, posx, posy, iden));
}

int	button_switch(t_data *game, int i)
{
	return (button_switch_master(game, i));
}
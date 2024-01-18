/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_public2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 00:08:31 by yannis            #+#    #+#             */
/*   Updated: 2024/01/18 01:43:55 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	int_exit_master(t_game *temp, int i);
int	say_master(t_game *temp, int i);
int	button_animation_master(void *data);

int int_exit(t_game *game, int i)
{
	return (int_exit_master(game, i));
}

int	say(t_game *temp, int i)
{
	return (say_master(temp, i));
}

int	button_animation(void *data)
{
	return (button_animation_master(data));
}
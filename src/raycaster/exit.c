/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:18:58 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/23 21:25:54 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	destroy_textures(t_data *data)
{
	mlx_destroy_image(data->mlx.mlx, data->textures.north.img);
	mlx_destroy_image(data->mlx.mlx, data->textures.west.img);
	mlx_destroy_image(data->mlx.mlx, data->textures.east.img);
	mlx_destroy_image(data->mlx.mlx, data->textures.south.img);
	mlx_destroy_image(data->mlx.mlx, data->textures.door.img);
}

void	exit_failure(t_data *data, char *msg)
{
	perror(msg);
	destroy_textures(data);
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	if (data->mlx.mlx)
		mlx_destroy_display(data->mlx.mlx);
	freeze(data->map);
	freeze(data->mlx.mlx);
	exit(EXIT_FAILURE);
}

int	exit_success(t_data *data)
{
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	destroy_textures(data);
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	if (data->mlx.mlx)
		mlx_destroy_display(data->mlx.mlx);
	freeze(data->map);
	freeze(data->mlx.mlx);
	exit(EXIT_SUCCESS);
}

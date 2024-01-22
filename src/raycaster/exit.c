/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:18:58 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/22 15:59:46 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	destroy_textures(t_data *data)
{
	mlx_destroy_image(data->mlx.mlx, data->textures.wall1.img);
	mlx_destroy_image(data->mlx.mlx, data->textures.wall2.img);
	mlx_destroy_image(data->mlx.mlx, data->textures.wall3.img);
	mlx_destroy_image(data->mlx.mlx, data->textures.wall4.img);
	mlx_destroy_image(data->mlx.mlx, data->textures.wall5.img);
	mlx_destroy_image(data->mlx.mlx, data->textures.wall6.img);
	mlx_destroy_image(data->mlx.mlx, data->textures.wall7.img);
	mlx_destroy_image(data->mlx.mlx, data->textures.wall8.img);
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

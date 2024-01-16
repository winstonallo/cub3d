/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:18:58 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/16 12:22:49 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	exit_failure(t_data *data, char *msg)
{
	perror(msg);
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	if (data->stone.img)
		mlx_destroy_image(data->mlx.mlx, data->stone.img);
	if (data->brick.img)
		mlx_destroy_image(data->mlx.mlx, data->brick.img);
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	if (data->mlx.mlx)
		mlx_destroy_display(data->mlx.mlx);
	freeze(data->map);
	freeze(data->mlx.mlx);
	exit(EXIT_FAILURE);
}

void	destroy_textures(t_data *data)
{
	mlx_destroy_image(data->mlx.mlx, data->brick.img);
	mlx_destroy_image(data->mlx.mlx, data->stone.img);
	mlx_destroy_image(data->mlx.mlx, data->pepe.img);
	mlx_destroy_image(data->mlx.mlx, data->wood.img);
	mlx_destroy_image(data->mlx.mlx, data->grass.img);
	mlx_destroy_image(data->mlx.mlx, data->metal.img);
	mlx_destroy_image(data->mlx.mlx, data->walltest.img);
	mlx_destroy_image(data->mlx.mlx, data->wall1.img);
	mlx_destroy_image(data->mlx.mlx, data->wall2.img);
	mlx_destroy_image(data->mlx.mlx, data->wall3.img);
	mlx_destroy_image(data->mlx.mlx, data->wall4.img);
	mlx_destroy_image(data->mlx.mlx, data->wall5.img);
	mlx_destroy_image(data->mlx.mlx, data->wall6.img);
	mlx_destroy_image(data->mlx.mlx, data->wall7.img);
	mlx_destroy_image(data->mlx.mlx, data->wall8.img);
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

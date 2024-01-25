/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:18:58 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 15:24:28 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

static void	free_data(t_data *data)
{
	freeze(data->no_txtr);
	freeze(data->we_txtr);
	freeze(data->ea_txtr);
	freeze(data->so_txtr);
	freeze(data->map);
	freeze(data->mlx.mlx);
}

static void	texture_destroy(t_data *data, t_txtr *texture)
{
	if (texture->img != NULL)
		mlx_destroy_image(data->mlx.mlx, texture->img);
}

static void	destroy_textures(t_data *data)
{
	texture_destroy(data, &data->textures.north);
	texture_destroy(data, &data->textures.south);
	texture_destroy(data, &data->textures.east);
	texture_destroy(data, &data->textures.west);
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
	free_data(data);
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
	free_data(data);
	exit(EXIT_SUCCESS);
}

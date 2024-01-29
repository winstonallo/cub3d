/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:18:58 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 14:28:45 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"
#include <unistd.h>

static void	free_data(t_data *data)
{
	freeze(data->no_txtr);
	freeze(data->we_txtr);
	freeze(data->ea_txtr);
	freeze(data->so_txtr);
	freeze(data->map);
	freeze(data->mlx.mlx);
}

void	exit_error(char *msg, t_data *data)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	free(data->map);
	exit(EXIT_FAILURE);
}

static void	destroy_textures(t_data *data)
{
	if (data->textures.north.img != NULL)
		mlx_destroy_image(data->mlx.mlx, data->textures.north.img);
	if (data->textures.south.img != NULL)
		mlx_destroy_image(data->mlx.mlx, data->textures.south.img);
	if (data->textures.east.img != NULL)
		mlx_destroy_image(data->mlx.mlx, data->textures.east.img);
	if (data->textures.west.img != NULL)
		mlx_destroy_image(data->mlx.mlx, data->textures.west.img);
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

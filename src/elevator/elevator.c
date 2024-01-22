/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 01:05:17 by yannis            #+#    #+#             */
/*   Updated: 2024/01/22 01:46:28 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/elevator.h"

int	elevator_init(t_data *data)
{
	write(1, "lol\n", 4);
	if (gif_init(data, "src/mlx_gif/gifs/ele-back/up/frame", -100, -100) < 0)
		return (perror("Error\nGif init in elevator failed"), -1);
	// if (gif_init(data, "src/mlx_gif/gifs/ele-left/frame", -100, -100) < 0)
	// 	return (perror("Error\nGif init in elevator failed"),
			// gif_delete(data, data->mlx.mlx), -1);
	if (gif_init(data, "src/mlx_gif/gifs/ele-right/up/frame", -100, -100) < 0)
		return (perror("Error\nGif init in elevator failed"),
			gif_delete(data, data->mlx.mlx), -1);
	// if (gif_init(data, "src/mlx_gif/gifs/ele-right/down/frame", -100, -100) < 0)
	// 	return (perror("Error\nGif init in elevator failed"),
	// 		gif_delete(data, data->mlx.mlx), -1);
	write(1, "lol\n", 4);
	data->elev.back_wall_up = data->gif[0];
	// data->elev.left_wall_up = data->gif[1];
	data->elev.right_wall_up = data->gif[1];
	// data->elev.right_wall_down = data->gif[3];
	write(1, "lol\n", 4);
	return (0);
}

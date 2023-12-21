/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:33:56 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/21 14:44:19 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	set_data_view(t_data *data)
{
	int		x;
	float	x_scale;
	float	y_scale;
	int		map_x;
	int		map_y;

	x_scale = (float)SCREEN_WIDTH / data->map_width;
	y_scale = (float)SCREEN_HEIGHT / data->map_height;
	x = -1;
	while (++x < data->map_height * data->map_width)
	{
		data->view_dir = isdirection(data->map[x]);
		if (data->view_dir)
		{
			map_x = (x % data->map_width);
			map_y = (x / data->map_height);
			data->player.x_pos = map_x;
			data->player.y_pos = map_y;
			data->player.x_screen_pos = map_x * x_scale + x_scale / 2;
			data->player.y_screen_pos = map_y * y_scale + y_scale / 2;
			return (set_directions(data));
		}
	}
}

float	min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

void	initialize_data(t_data *data)
{
	int	player_pos;

	data->mlx.mlx = NULL;
	data->mlx.win = NULL;
	data->mlx.img = NULL;
	data->stone.img = NULL;
	data->brick.img = NULL;
	data->pepe.img = NULL;
	data->view_dir = 0;
	data->map_width = 33;
	data->map_height = 14;
	data->player.angle = PI / 2;
	data->x_scale = (float)SCREEN_WIDTH / 8;
	data->y_scale = (float)SCREEN_HEIGHT / 8;
	data->win_width = SCREEN_WIDTH;
	data->win_height = SCREEN_HEIGHT;
	data->line_color = 0x33ff00;
	data->player.x_dir = cos(data->player.angle) * 5;
	data->player.y_dir = sin(data->player.angle) * 5;
	data->map_size = data->map_height * data->map_width;
	data->min_distance = 0;
	player_pos = map_get_player_pos(data->map);
	data->player.x_pos = player_pos % data->map_width;
	data->player.y_pos = (float)player_pos / data->map_width;
}

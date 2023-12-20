/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:33:56 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/20 21:27:39 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	set_data_view(t_data *data)
{
	int		x;
	float	tile_width;
	float	tile_height;
	int		map_x;
	int		map_y;

	tile_width = (float)SCREEN_WIDTH / data->map_width;
	tile_height = (float)SCREEN_HEIGHT / data->map_height;
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
			data->player.x_screen_pos = map_x * tile_width + tile_width / 2;
			data->player.y_screen_pos = map_y * tile_height + tile_height / 2;
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
	data->mlx.mlx = NULL;
	data->mlx.win = NULL;
	data->mlx.img = NULL;
	data->map_width = 8;
	data->map_height = 8;
	data->player.angle = PI / 2;
	data->tile_width = (float)SCREEN_WIDTH / data->map_width;
	data->tile_height = (float)SCREEN_HEIGHT / data->map_height;
	data->scale_factor = min(data->tile_width, data->tile_height);
	data->win_width = SCREEN_WIDTH;
	data->win_height = SCREEN_HEIGHT;
	data->floor_color = 0xffffff;
	data->wall_color = 0xFFC0CB;
	data->player_color = 0x000000;
	data->line_color = 0x33ff00;
	data->player.x_dir = cos(data->player.angle) * 5;
	data->player.y_dir = sin(data->player.angle) * 5;
	data->map_size = data->map_height * data->map_width;
	data->min_distance = 0;
}

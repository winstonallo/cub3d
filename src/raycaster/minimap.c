/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:11 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 19:07:28 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	set_scaling_factor(t_data *data)
{
	if (data->map_width <= 60)
		data->map_scale_x = 12;
	else if (data->map_width <= 80)
		data->map_scale_x = 9;
	else
		data->map_scale_x = 6;
	if (data->map_height <= 60)
		data->map_scale_y = 6;
	else if (data->map_height <= 80)
		data->map_scale_y = 4;
	else
		data->map_scale_y = 3;
}

void	draw_map_element(t_line line, t_data *data, int x)
{
	while (++line.y0 < line.y1)
	{
		line.x0 = x;
		while (++line.x0 < line.x1)
			put_pixel(data, line.x0, line.y0, 0xffffff);
	}
}

void	draw_map(t_data *data)
{
	int		x;
	int		xx;
	int		y;
	t_line	line;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			if (data->map[y * data->map_width + x] == 1)
			{
				xx = x * data->map_scale_x - 1;
				line.y0 = y * data->map_scale_y - 1;
				line.x1 = (x + 1) * data->map_scale_x - 2;
				line.y1 = (y + 1) * data->map_scale_y - 2;
				draw_map_element(line, data, xx);
			}
			else
				continue ;
		}
	}
}

void	draw_player(t_data *data)
{
	int	player_pos_x;
	int	player_pos_y;

	player_pos_x = data->player.x_pos * data->map_scale_x;
	player_pos_y = data->player.y_pos * data->map_scale_y;
	draw_circle(data, player_pos_x, player_pos_y, 2);
}

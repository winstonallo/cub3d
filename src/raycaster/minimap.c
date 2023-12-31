/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/21 12:56:19 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

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
				xx = x * 10 - 1;
				line.y0 = y * 10 - 1;
				line.x1 = (x + 1) * 10 - 2;
				line.y1 = (y + 1) * 10 - 2;
				draw_map_element(line, data, xx);
			}
			else
				continue ;
		}
	}
}

void	init_line(t_line *line, t_data *data, int length)
{
	if (!length)
		length = 1;
	line->x0 = data->player.x_pos;
	line->y0 = data->player.y_pos;
	line->x1 = (data->player.x_pos + data->player.x_dir);
	line->y1 = (data->player.y_pos + data->player.y_dir);
}

void	draw_player(t_data *data)
{
	draw_circle(data, data->player.x_pos * 10, data->player.y_pos * 10, 2);
}

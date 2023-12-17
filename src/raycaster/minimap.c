/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/17 23:06:35 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void draw_map(t_data *data)
{
    int 	x;
	int		y;
    int 	color;
    t_line line;
	
	x = 0;
	y = 0;
    data->tile_width = (float)SCREEN_WIDTH / data->map_width;
    data->tile_height = (float)SCREEN_HEIGHT / data->map_height;
    for (y = 0; y < data->map_height; y++)
    {
        for (x = 0; x < data->map_width; x++)
        {
            if (data->map[y * data->map_width + x] == 1)
                color = 0xffffff;
            else
                color = 0x000000;
            line.x0 = x * 30;
            line.y0 = y * 30;
            line.x1 = (x + 1) * 30;  
            line.y1 = (y + 1) * 30;
            for (int py = line.y0; py < line.y1; py++)
                for (int px = line.x0; px < line.x1; px++)
                    put_pixel(data, px, py, color);
        }
    }
	draw_player(data);
}

void	init_line(t_line *line, t_data *data, int length)
{
	if (!length)
		length = 1;
	line->x0 = data->player.x_pos * 30;
	line->y0 = data->player.y_pos * 30;
	line->x1 = (data->player.x_pos + data->player.x_dir) * 30;
	line->y1 = (data->player.y_pos + data->player.y_dir) * 30;
	line->thickness = 1;
}

void	draw_player(t_data *data)
{
	draw_circle(data, data->player.x_pos * 30, data->player.y_pos * 30, 8);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/17 12:36:10 by abied-ch         ###   ########.fr       */
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
                color = data->wall_color;
            else
                color = data->floor_color;
            line.x0 = x * data->tile_width;
            line.y0 = y * data->tile_height;
            line.x1 = (x + 1) * data->tile_width -2;  
            line.y1 = (y + 1) * data->tile_height -2;
            for (int py = line.y0; py < line.y1; py++)
                for (int px = line.x0; px < line.x1; px++)
                    put_pixel(data, px, py, color);
        }
    }
    draw_player(data);
}

void	init_line(t_line *line, t_data *data, int length)
{
	line->x0 = data->player.x_screen_pos;
	line->y0 = data->player.y_screen_pos;
	line->x1 = data->player.x_screen_pos + data->player.x_dir * length;
	line->y1 = data->player.y_screen_pos + data->player.y_dir * length;
	line->thickness = 1;
}

void	draw_player(t_data *data)
{
	t_line	line;
	
	init_line(&line,  data, 10);
	draw_circle(data, data->player.x_screen_pos, data->player.y_screen_pos, 8);
	raycast(data);
	draw_line(data, line, 0x00f0ff, 4);
}
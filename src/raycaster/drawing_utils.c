/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:32:42 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/22 15:16:05 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = data->img.addr + (y * data->img.l_l + x * (data->img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_tile(t_data *data, int x, int y, char tile)
{
	int	pos_y;
	int	pos_x;

	if (tile != 1)
		return ;
	pos_y = y - 1;
	while (++pos_y < data->y_scale)
	{
		pos_x = x - 1;
		while (++pos_x < SCALE)
			put_pixel(data, pos_x, pos_y, HEXA_WHITE);
	}
}

void	draw_circle(t_data *data, int x, int y, int size)
{
	int	pos_y;
	int	pos_x;

	pos_y = y - size - 1;
	while (++pos_y <= y + size)
	{
		pos_x = x - size - 1;
		while (++pos_x <= x + size)
			if ((pos_x - x) * (pos_x - x) + (pos_y - y)
				* (pos_y - y) <= size * size)
				put_pixel(data, pos_x, pos_y, 0xffffff);
	}
}

void	set_line_vars(t_line *line, int size)
{
	line->step = -1;
	line->neg_size = -(size / 2) - 1;
	line->x_step = line->x1 - line->x0;
	line->y_step = line->y1 - line->y0;
	line->max = fmax(fabs(line->x_step), fabs(line->y_step));
	line->x_step /= line->max;
	line->y_step /= line->max;
}

void	draw_line(t_data *data, t_line line, int color, int size)
{
	int		dx;
	int		dy;

	if (line.scale == MAPSIZE)
	{
		line.x0 = line.x0 / SCALE * 10;
		line.x1 = line.x1 / SCALE * 10;
		line.y0 = line.y0 / SCALE * 10;
		line.y1 = line.y1 / SCALE * 10;
	}
	set_line_vars(&line, size);
	while (++line.step <= line.max)
	{
		dx = line.neg_size;
		while (++dx < size)
		{
			dy = line.neg_size;
			while (++dy < size)
				put_pixel(data, line.x0 + dx, line.y0 + dy, color);
		}
		line.x0 += line.x_step;
		line.y0 += line.y_step;
	}
}

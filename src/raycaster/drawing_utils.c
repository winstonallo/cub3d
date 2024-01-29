/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:32:42 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 15:33:02 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	draw_background(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			if (y < SCREEN_HEIGHT / 2)
				put_pixel(data, x, y, data->ceiling_color);
			else
				put_pixel(data, x, y, data->floor_color);
		}
	}
}

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
	int	x_inc;

	if (tile != 1)
		return ;
	while (y < data->y_scale)
	{
		x_inc = x;
		while (x_inc < SCALE)
		{
			put_pixel(data, x_inc, y, HEXA_WHITE);
			x_inc++;
		}
		y++;
	}
}

void	draw_circle(t_data *data, int x, int y, int size)
{
	int	pos_y;
	int	pos_x;

	pos_y = y - size;
	while (pos_y <= y + size)
	{
		pos_x = x - size;
		while (pos_x <= x + size)
		{
			if (is_inside_circle(pos_x - x, pos_y - y, size))
				put_pixel(data, pos_x, pos_y, HEXA_WHITE);
			pos_x++;
		}
		pos_y++;
	}
}

void	draw_line(t_data *data, t_line line, int color, int size)
{
	int		width;
	int		length;

	if (line.scale == MAPSIZE)
		scale_line_to_minimap(&line, data);
	set_line_vars(&line, size);
	while (line.step <= line.max)
	{
		width = line.neg_size;
		while (width < size)
		{
			length = line.neg_size;
			while (++length < size)
			{
				put_pixel(data, line.x0 + width, line.y0 + length, color);
				length++;
			}
			width++;
		}
		line.x0 += line.x_step;
		line.y0 += line.y_step;
		line.step++;
	}
}

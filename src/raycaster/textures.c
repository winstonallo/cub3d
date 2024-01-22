/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:31:37 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/22 15:29:37 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	draw_background(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	data->ceiling_color = HEXA_MIDNIGHT_BLUE;
	data->floor_color = HEXA_BLACK;
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

void	set_texture(t_data *data, t_txtr *texture)
{
	if (data->door == true)
		*texture = data->textures.wall8;
	if (data->hit == NORTH)
		*texture = data->textures.wall1;
	else if (data->hit == EAST)
		*texture = data->textures.wall2;
	else if (data->hit == SOUTH)
		*texture = data->textures.wall3;
	else if (data->hit == WEST)
		*texture = data->textures.wall5;
}

int	get_pixel(t_txtr *texture, int x, int y)
{
	int		color;
	char	*dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x000000);
	dst = texture->addr + (y * texture->l_l + x * (texture->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	set_hit_position(t_data *data)
{
	data->hit_pos = fmod(data->hit_pos / HIT_POS_OFFSET, data->map_width);
	data->hit_pos /= data->map_width;
}

void	draw_texture(t_data *data, int x, t_line line, t_txtr *texture)
{
	int		color;
	int		y;
	int		texture_y;
	int		screen_y;
	int		texture_x;

	set_hit_position(data);
	y = -1;
	while (++y < line.wall_height)
	{
		if (texture->height == 0)
			break ;
		texture_y = (int)((float)y / (float)line.wall_height * texture->height)
			% texture->height;
		texture_x = (int)((data->hit_pos) * (float)texture->width);
		color = get_pixel(texture, texture_x, texture_y);
		screen_y = line.y0 + y;
		if (screen_y >= 0 && screen_y < SCREEN_HEIGHT)
			put_pixel(data, x, screen_y, color);
	}
}

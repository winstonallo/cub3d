/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:27:06 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/16 22:22:26 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	t_color	get_pixel_color(t_img *img_data, int x, int y)
{
	t_color	color;
	char	*pixel_addr;
	int		pixel_color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;
	if (x >= 0 && x < (img_data->line_len / (img_data->bits_per_pixel / 8))
		&& y >= 0 && y < img_data->line_len)
	{
		pixel_addr = img_data->addr + (y * img_data->line_len
				+ x * (img_data->bits_per_pixel / 8));
		pixel_color = *(int *)pixel_addr;
		color.r = (pixel_color >> 16) & 0xFF;
		color.g = (pixel_color >> 8) & 0xFF;
		color.b = pixel_color & 0xFF;
		color.a = (pixel_color >> 24) & 0xFF;
	}
	return (color);
}

static	int	change_pixel(t_img *img_data, int x, int y, int color)
{
	int	pixel_position;
	int	*pixel_address;

	pixel_position = y * img_data->line_len
		+ x * (img_data->bits_per_pixel / 8);
	pixel_address = (int *)(img_data->addr + pixel_position);
	if (color == -1)
		return (*pixel_address);
	*pixel_address = color;
	return (0);
}

void	image_edit(t_game *g, t_img *base, t_img to_copy, int identifier)
{
	t_color	p_c;
	int		x;
	int		y;

	base->addr = mlx_get_data_addr(base->img, &base->bits_per_pixel,
			&base->line_len, &base->endian);
	to_copy.addr = mlx_get_data_addr(to_copy.img, &to_copy.bits_per_pixel,
			&to_copy.line_len, &to_copy.endian);
	y = -1;
	while (++y < to_copy.height)
	{
		x = -1;
		while (++x < to_copy.width)
		{
			p_c = get_pixel_color(&to_copy, x, y);
			if (identifier == 1)
				if (p_c.r == 255 && p_c.g == 255 && p_c.b == 255)
					change_pixel(base, x + g->cords.img_x,
						y + g->cords.img_y, to_copy.color);
			if (identifier != 1)
				change_pixel(base, x + g->cords.img_x,
					y + g->cords.img_y, change_pixel(&to_copy, x, y, -1));
		}
	}
}

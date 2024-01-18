/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:27:06 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/18 02:51:07 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

static	t_color	get_pixel_color(t_txtr *img_data, int x, int y)
{
	t_color	color;
	char	*pixel_addr;
	int		pixel_color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;
	if (x >= 0 && x < (img_data->l_l / (img_data->bpp / 8))
		&& y >= 0 && y < img_data->l_l)
	{
		pixel_addr = img_data->addr + (y * img_data->l_l
				+ x * (img_data->bpp / 8));
		pixel_color = *(int *)pixel_addr;
		color.r = (pixel_color >> 16) & 0xFF;
		color.g = (pixel_color >> 8) & 0xFF;
		color.b = pixel_color & 0xFF;
		color.a = (pixel_color >> 24) & 0xFF;
	}
	return (color);
}

static	int	change_pixel(t_txtr *img_data, int x, int y, int color)
{
	int	pixel_position;
	int	*pixel_address;

	pixel_position = y * img_data->l_l
		+ x * (img_data->bpp / 8);
	pixel_address = (int *)(img_data->addr + pixel_position);
	if (color == -1)
		return (*pixel_address);
	*pixel_address = color;
	return (0);
}

void	image_edit(t_data *g, t_txtr *base, t_txtr to_copy, int identifier)
{
	t_color	p_c;
	int		x;
	int		y;

	base->addr = mlx_get_data_addr(base->img, &base->bpp,
			&base->l_l, &base->endian);
	to_copy.addr = mlx_get_data_addr(to_copy.img, &to_copy.bpp,
			&to_copy.l_l, &to_copy.endian);
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

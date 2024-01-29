/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:31:37 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 14:36:19 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	get_texture_data(t_txtr *t, t_data *data, char *path)
{
	t->img = mlx_xpm_file_to_image(data->mlx.mlx, path, &t->width, &t->height);
	if (t->img == NULL)
		exit_failure(data, "Error\nimage initialization failed");
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->l_l, &t->endian);
}

void	set_texture(t_data *data, t_txtr *texture)
{
	if (data->hit == NORTH)
		*texture = data->textures.north;
	else if (data->hit == EAST)
		*texture = data->textures.east;
	else if (data->hit == SOUTH)
		*texture = data->textures.south;
	else if (data->hit == WEST)
		*texture = data->textures.west;
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
	data->hit_pos = fmod(data->hit_pos / data->scaling, data->map_width);
	data->hit_pos /= data->map_width;
}

void	draw_texture(t_data *data, int x, t_line line, t_txtr *t)
{
	int		color;
	int		y;
	int		txtr_y;
	int		txtr_x;
	int		screen_y;

	set_hit_position(data);
	y = -1;
	while (++y < line.wall_height)
	{
		txtr_y = (int)((double)y / line.wall_height * t->height) % t->height;
		txtr_x = (int)((data->hit_pos) * (double)t->width);
		color = get_pixel(t, txtr_x, txtr_y);
		screen_y = line.y0 + y;
		if (screen_y >= 0 && screen_y < SCREEN_HEIGHT)
			put_pixel(data, x, screen_y, color);
	}
}

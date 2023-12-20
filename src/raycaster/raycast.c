/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:34 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/20 19:22:27 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	init_vars_horizontal(t_raycast *h_ray, t_player *player, float angle)
{
	h_ray->angle = angle;
	h_ray->max_depth = 0;
	h_ray->a_tan = -1 / tan(h_ray->angle);
	if (angle > PI)
	{
		h_ray->reach_y = (int)player->y_pos - 0.0001;
		h_ray->reach_x = ((player->y_pos - h_ray->reach_y) * h_ray->a_tan
				+ player->x_pos);
		h_ray->inc_y = -1;
		h_ray->inc_x = -h_ray->inc_y * h_ray->a_tan;
	}
	else if (h_ray->angle < PI)
	{
		h_ray->reach_y = (int)player->y_pos + 1;
		h_ray->reach_x = (player->y_pos - h_ray->reach_y) * h_ray->a_tan
			+ player->x_pos;
		h_ray->inc_y = 1;
		h_ray->inc_x = -h_ray->inc_y * h_ray->a_tan;
	}
	else if (!h_ray->angle || h_ray->angle == (float)PI)
	{
		h_ray->reach_x = player->x_pos;
		h_ray->reach_y = player->y_pos;
		h_ray->max_depth = 8;
	}
}


void	init_vars_vertical(t_raycast *v_ray, t_player *player, float angle)
{
	v_ray->angle = angle;
	v_ray->max_depth = 0;
	v_ray->n_tan = -tan(v_ray->angle);
	if (v_ray->angle > P2 && v_ray->angle < P3)
	{
		v_ray->reach_x = (int)player->x_pos - 0.0001;
		v_ray->reach_y = (player->x_pos - v_ray->reach_x)
			* v_ray->n_tan + player->y_pos;
		v_ray->inc_x = -1;
		v_ray->inc_y = -v_ray->inc_x * v_ray->n_tan;
	}
	else if (v_ray->angle < P2 || v_ray->angle > P3)
	{
		v_ray->reach_x = (int)player->x_pos + 1;
		v_ray->reach_y = (player->x_pos - v_ray->reach_x)
			* v_ray->n_tan + player->y_pos;
		v_ray->inc_x = 1;
		v_ray->inc_y = -v_ray->inc_x * v_ray->n_tan;
	}
	else if (!v_ray->angle || v_ray->angle == (float)PI)
	{
		v_ray->reach_y = player->y_pos;
		v_ray->reach_x = player->x_pos;
		v_ray->max_depth = 8;
	}
}

static int	collision(t_data *data, float new_x, float new_y)
{
	int map_pos;

	map_pos = (int)(new_y) * data->map_width + (int)(new_x);
	if (map_pos < 0 || map_pos > data->map_width * data->map_height)
		return (EXIT_FAILURE);
	if (data->map[map_pos] != 1)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	scan(t_raycast *ray, t_data *data)
{
	while (ray->max_depth < data->map_width)
	{
		ray->map_x = ((int)ray->reach_x);
		ray->map_y = ((int)ray->reach_y);
		ray->map_pos = ray->map_y * data->map_width + ray->map_x;
		if (collision(data, ray->reach_x, ray->reach_y))
			break ;
		else
		{
			ray->reach_x += ray->inc_x;
			ray->reach_y += ray->inc_y;
			ray->max_depth++;
		}
	}
}

void	draw_rays(t_data *data, float angle)
{
	t_line		v_line;
	t_line		h_line;
	t_raycast	vertical;
	t_raycast	horizontal;

	init_vars_horizontal(&horizontal, &data->player, angle);
	init_vars_vertical(&vertical, &data->player, angle);
	scan(&horizontal, data);
	scan(&vertical, data);
	get_line(&h_line, horizontal, data);
	get_line(&v_line, vertical, data);
	return (calculate_distance(data, v_line, h_line));
}

int	get_pixel(t_data *data, int x, int y)
{
	int		color;
	char	*dst;

	dst = data->texture.addr + (y * data->img.l_l + x * (data->img.bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	draw_texture(t_data *data, t_line line, int x, int y)
{
	int		i;
	int		j;
	int		color;
	float	scale_x;
	float	scale_y;

	i = -1;
	scale_x = (float)line.scale / (float)line.x1;
	scale_y = (float)line.scale / (float)line.y1;
	while (++i < line.x1)
	{
		j = -1;
		while (++j < line.y1)
		{
			color = get_pixel(data, x + i * scale_x, y + j * scale_y);
			if (color != 0x000000)
				put_pixel(data, line.x0 + i, line.y0 + j, color);
		}
	}
}

void	raycast(t_data *data)
{
	t_line	line1;
	int		i;
	float	angle;	

	i = -1;
	angle = fmod(data->player.angle - DR * 60, 2 * PI);
	while (++i < 120)
	{
		data->min_distance = MAX_DIST;
		draw_rays(data, angle);
		draw_line(data, data->shortest_line, 0x00ff00, 1);
		adjust_vars(data, angle);
		get_3d_line(&line1, i, data);
		draw_texture(data, line1, data->wall_color, 2);
		angle += (float)DR;
		angle = fmod(angle, 2 * PI);
	}
	draw_map(data);
	draw_player(data);
}

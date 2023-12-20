/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:34 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/20 22:08:31 by abied-ch         ###   ########.fr       */
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

	if (x < 0 || x >= data->texture.width || y < 0 || y >= data->texture.height)
		return (0x000000);
	dst = data->texture.addr + (y * data->texture.l_l + x * (data->texture.bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void draw_texture(t_data *data, int x, int wall_height, int texture_offset_x, t_line line) {
    int color;
    // float scale_y = (float)data->texture.height / (float)wall_height;

	if (texture_offset_x)
	{}
    for (int y = 0; y < wall_height; y++) {
        // Calculate where this pixel is in relation to the texture
        float percent_of_texture = (float)y / (float)wall_height;
        int tex_y = (int)(percent_of_texture * data->texture.height);
        color = get_pixel(data, x % data->texture.width, tex_y % data->texture.height);

        // Calculate the screen y coordinate
        int screen_y = line.y0 + y;
        
        // Draw the pixel if it's within screen bounds
        if (screen_y >= 0 && screen_y < SCREEN_HEIGHT) {
            put_pixel(data, x, screen_y, color);
        }
    }
}



void	raycast(t_data *data)
{
	t_line	line1;
	int		i;
	int		texture_offset_x;

	i = -1;

	float angle = data->player.angle + (-FIELD_OF_VIEW / 2);
	while (++i < SCREEN_WIDTH)
	{
		data->min_distance = MAX_DIST;
		draw_rays(data, angle);
		draw_line(data, data->shortest_line, 0x00ff00, 1);
		adjust_vars(data, angle);
		get_3d_line(&line1, i, data);
		int texture_hit_position = (int)(data->x_scale * data->min_distance);
		texture_offset_x = (int)(texture_hit_position * data->texture.width);
		int projected_wall_height = line1.y1 - line1.y0;
		draw_texture(data, i, projected_wall_height, texture_offset_x, line1);
		angle += FIELD_OF_VIEW / SCREEN_WIDTH;
		angle = fmod(angle, 2 * PI);
	}
	draw_map(data);
	draw_player(data);
}

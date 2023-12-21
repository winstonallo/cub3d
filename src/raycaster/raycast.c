/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:34 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/21 10:21:30 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void init_vars_horizontal(t_raycast *h_ray, t_player *player, float angle)
{
    h_ray->max_depth = 0;
	h_ray->a_tan = -1 / tan(angle);
	if (angle > PI)
	{
	    h_ray->reach_y = (int)player->y_pos - 0.0001;
	    h_ray->inc_y = -1;
	}
	else if (angle < PI)
	{
	    h_ray->reach_y = (int)player->y_pos + 1.0001;
		h_ray->inc_y = 1;
	}
	else
	{
	    h_ray->reach_y = player->y_pos;
	    h_ray->inc_y = 0;
	    h_ray->max_depth = 8;
	}
	h_ray->reach_x = (player->y_pos - h_ray->reach_y) * h_ray->a_tan + player->x_pos;
	h_ray->inc_x = -h_ray->inc_y * (h_ray->a_tan);
}



void	init_vars_vertical(t_raycast *v_ray, t_player *player, float angle)
{
	v_ray->max_depth = 0;
	v_ray->n_tan = -tan(angle);
	if (angle > P2 && angle < P3)
	{
		v_ray->reach_x = (int)player->x_pos - 0.0001;
		v_ray->inc_x = -1;
	}
	else if (angle < P2 || angle > P3)
	{
		v_ray->reach_x = (int)player->x_pos + 1;
		v_ray->inc_x = 1;
	}
	else
	{
		v_ray->inc_x = 0;
		v_ray->reach_x = player->x_pos;
		v_ray->max_depth = 8;
	}
	v_ray->reach_y = (player->x_pos - v_ray->reach_x) * v_ray->n_tan + player->y_pos;
	v_ray->inc_y = -v_ray->inc_x * v_ray->n_tan;
}

static bool	collision(t_data *data, float new_x, float new_y)
{
	int map_pos;

	map_pos = (int)(new_y) * data->map_width + (int)(new_x);
	if (map_pos < 0 || map_pos > data->map_width * data->map_height)
		return (true);
	if (data->map[map_pos] != 1)
		return (false);
	return (true);
}

void	scan(t_raycast *ray, t_data *data)
{
	while (ray->max_depth < data->map_width)
	{
		ray->map_x = ((int)ray->reach_x);
		ray->map_y = ((int)ray->reach_y);
		ray->map_pos = ray->map_y * data->map_width + ray->map_x;
		if (collision(data, ray->reach_x, ray->reach_y))
		{
			ray->hit_status = SUCCESS;
			break ;
		}
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




int	get_pixel(t_texture *texture, int x, int y)
{
	int		color;
	char	*dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x000000);
	dst = texture->addr + (y * texture->l_l + x * (texture->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

float calculate_scale_factor(float ray_distance, float map_tile_size)
{
    const float perceived_tile_size_at_one_unit_distance = 0.5f;

    // Prevent division by zero
    if (ray_distance <= 0.0f) {
        ray_distance = 0.01f;
    }

    // Calculate the scale factor based on the distance
    float scale_factor = perceived_tile_size_at_one_unit_distance / ray_distance;

    // Adjust the scale factor based on the actual size of your map tiles
    scale_factor *= map_tile_size / perceived_tile_size_at_one_unit_distance;

    return scale_factor;
}


void draw_texture(t_data *data, int x, int wall_height, t_line line, t_texture *texture)
{
    int color;
    int y;
    int texture_y;
    int screen_y;
    float percent_of_texture;
    // float texture_scale_factor = calculate_scale_factor(data->min_distance, 1);

    y = -1;
    while (++y < wall_height)
    {
        percent_of_texture = (float)y / (float)wall_height;
        texture_y = (int)(percent_of_texture * texture->height/*  * texture_scale_factor */) % texture->height;
        color = get_pixel(texture, x % texture->width, texture_y);
        screen_y = line.y0 + y;
        if (screen_y >= 0 && screen_y < SCREEN_HEIGHT)
            put_pixel(data, x, screen_y, color);
    }
}



void	raycast(t_data *data)
{
	t_line	line1;
	int		i;

	i = -1;
	float angle = data->player.angle + (-FIELD_OF_VIEW / 2);
	if (angle < 0)
		angle += 2 * PI;
	else if (angle > 2 * PI)
		angle -= 2 * PI;
	while (++i < SCREEN_WIDTH)
	{
		data->min_distance = MAX_DIST;
		draw_rays(data, angle);
		draw_line(data, data->shortest_line, 0x00ff00, 1);
		adjust_vars(data, angle);
		get_3d_line(&line1, i, data);
		int projected_wall_height = line1.y1 - line1.y0;
		if (data->hit == NORTH)
			draw_texture(data, i, projected_wall_height, line1, &data->brick);
		else if (data->hit == EAST)
			draw_texture(data, i, projected_wall_height, line1, &data->stone);
		angle += FIELD_OF_VIEW / (SCREEN_WIDTH);
		if (angle < 0)
			angle += 2 * PI;
		else if (angle > 2 * PI)
			angle -= 2 * PI;
	}
	draw_map(data);
	draw_player(data);
}

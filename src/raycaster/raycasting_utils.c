/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/17 14:27:07 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	horizontal_scan(t_raycast *ray, t_data *data)
{
	while (ray->max_depth < 8 && ++ray->loop_protection < MAX_DISTANCE)
	{
		ray->map_x = abs((int)ray->reach_x/*  >> 6 */);
		ray->map_y = abs((int)ray->reach_y/*  >> 6 */);
		ray->map_pos = ray->map_y * data->map_width + ray->map_x;
		if (ray->map_pos > 0 && ray->map_pos < data->map_size && data->map[ray->map_pos] == 1)
		{
			print_test_raycasting(data, ray->loop_protection, WEST, ray);
			ray->max_depth = 8;
		}
		else
		{
			ray->reach_x += ray->inc_x;
			ray->reach_y += ray->inc_y;
			ray->max_depth++;
		}
		if (ray->map_pos > 0 && ray->map_pos < data->map_size && ray->max_depth == 8 && data->map[ray->map_pos] != 1)
			data->error = NO_WALL_HIT;
		else
			data->error = SUCCESS;
		}
	}


void	init_vars_horizontal(t_raycast *ray, t_player *player, t_data *data)
{
	if (data)
	{}
	ray->horizontal_distance = 100000;
	if (ray->angle > PI)//looking downwards
	{
		ray->reach_y = (((int)player->y_pos/*  / data->map_size */)/*  * data->map_size */) - 0.0001;
		ray->reach_x = ((player->y_pos - ray->reach_y) * ray->a_tan + player->x_pos);
		ray->inc_y = -1;
		ray->inc_x = -ray->inc_y * ray->a_tan;
	}
	if (ray->angle < PI)//looking upwards
	{
		ray->reach_y = (((int)player->y_pos/*  / data->map_size */)/*  * data->map_size */);
		ray->reach_x = ((player->y_pos - ray->reach_y) * ray->a_tan + player->x_pos);
		ray->inc_y = 1;
		ray->inc_x = -ray->inc_y * ray->a_tan;
	}
	if (!ray->angle)//straight left/right
	{
		ray->reach_x = player->x_pos;
		ray->reach_y = player->y_pos;
		ray->max_depth = 1;	
	}
}
void	vertical_scan(t_raycast *ray, t_data *data)
{
	while (ray->max_depth < 8 && ++ray->loop_protection < MAX_DISTANCE)
	{
		ray->map_x = abs((int)ray->reach_x/*  / data->map_size */);
		ray->map_y = abs((int)ray->reach_y/*  / data->map_size */);
		ray->map_pos = ray->map_y * data->map_width + ray->map_x;
		if (ray->map_pos > 0 && ray->map_pos < data->map_size && data->map[ray->map_pos] == 1)
		{
			print_test_raycasting(data, ray->loop_protection, UP, ray);
			ray->max_depth = 8;
		}
		else
		{
			ray->reach_x += ray->inc_x;
			ray->reach_y += ray->inc_y;
			ray->max_depth++;
		}
		if (ray->map_pos > 0 && ray->map_pos < data->map_size && ray->max_depth == 8 && data->map[ray->map_pos] != 1)
			data->error = NO_WALL_HIT;
		else
			data->error = SUCCESS;
	}
}

void	init_vars_vertical(t_raycast *ray, t_player *player, t_data *data)
{
	ray->vertical_distance = 100000;
	if (data)
	{}
	if (ray->angle > P2 && ray->angle < P3)
	{
		ray->reach_x = (((int)player->x_pos/*  / data->map_size */)/*  * data->map_size */) - 0.0001;
		ray->reach_y = (player->x_pos - ray->reach_x) * ray->n_tan + player->y_pos;
		ray->inc_x = -1;
		ray->inc_y = -ray->inc_x * ray->n_tan;
	}
	if (ray->angle < P2 || ray->angle > P3)
	{
		ray->reach_x = (((int)player->x_pos/*  / data->map_size */)/*  * data->map_size */);
		ray->reach_y = (player->x_pos - ray->reach_x) * ray->n_tan + player->y_pos;
		ray->inc_x = 1;
		ray->inc_y = -ray->inc_x * ray->n_tan;
	}
	if (!ray->angle || ray->angle == PI)
	{
		ray->reach_y = player->y_pos;	
		ray->reach_x = player->x_pos;
		ray->max_depth = 8;	
	}
}

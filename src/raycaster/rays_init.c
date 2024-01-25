/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:43:48 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 12:45:05 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	horizontal_vars_init(t_raycast *h_ray, t_player *p, double angle)
{
	h_ray->max_depth = 0;
	h_ray->a_tan = -1 / tan(angle);
	if (angle > PI)
	{
		h_ray->reach_y = (int)p->y_pos - 0.0001;
		h_ray->inc_y = -1;
	}
	else if (angle < PI)
	{
		h_ray->reach_y = (int)p->y_pos + 1;
		h_ray->inc_y = 1;
	}
	else
	{
		h_ray->reach_y = p->y_pos;
		h_ray->inc_y = 0;
		h_ray->max_depth = 33;
	}
	h_ray->reach_x = (p->y_pos - h_ray->reach_y)
		* h_ray->a_tan + p->x_pos;
	h_ray->inc_x = -h_ray->inc_y * (h_ray->a_tan);
}

void	vertical_vars_init(t_raycast *v_ray, t_player *p, double angle)
{
	v_ray->max_depth = 0;
	v_ray->n_tan = -tan(angle);
	if (angle > P2 && angle < P3)
	{
		v_ray->reach_x = (int)p->x_pos - 0.0001;
		v_ray->inc_x = -1;
	}
	else if (angle < P2 || angle > P3)
	{
		v_ray->reach_x = (int)p->x_pos + 1;
		v_ray->inc_x = 1;
	}
	else
	{
		v_ray->inc_x = 0;
		v_ray->reach_x = p->x_pos;
		v_ray->max_depth = 33;
	}
	v_ray->reach_y = (p->x_pos - v_ray->reach_x)
		* v_ray->n_tan + p->y_pos;
	v_ray->inc_y = -v_ray->inc_x * v_ray->n_tan;
}

void	scan(t_raycast *ray, t_data *data, int max)
{
	while (ray->max_depth < max)
	{
		ray->map_x = ((int)ray->reach_x);
		ray->map_y = ((int)ray->reach_y);
		ray->map_pos = ray->map_y * data->map_width + ray->map_x;
		if (collision(data, ray->reach_x, ray->reach_y))
			return ;
		else
		{
			ray->reach_x += ray->inc_x;
			ray->reach_y += ray->inc_y;
			ray->max_depth++;
		}
	}
}

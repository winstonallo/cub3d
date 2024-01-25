/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:29:33 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 15:20:51 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

bool	collision(t_data *data, double new_x, double new_y)
{
	int	map_pos;

	map_pos = (int)new_y * data->map_width + (int)new_x;
	if (map_pos < 0 || map_pos > data->map_width * data->map_height)
		return (true);
	if (data->map[map_pos] != 1)
		return (false);
	return (true);
}

void	normalize_angle(double *angle, double increment)
{
	*angle += increment;
	if (*angle < 0)
		*angle += 2 * PI;
	else if (*angle > 2 * PI)
		*angle -= 2 * PI;
}

double	dist(t_line line)
{
	return (sqrt(pow(line.x1 - line.x0, 2) + pow(line.y1 - line.y0, 2)));
}

bool	is_not_wall(int a, int b, int c, int d)
{
	return (a != 1 && b != 1 && c != 1 && d != 1);
}

bool	is_inside_circle(int x, int y, int size)
{
	return (pow(x, 2) + pow(y, 2) <= pow(size, 2));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:29:33 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/16 12:45:34 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

bool	collision(t_data *data, float new_x, float new_y)
{
	int	map_pos;

	map_pos = (int)new_y * data->map_width + (int)new_x;
	if (map_pos < 0 || map_pos > data->map_width * data->map_height)
		return (true);
	if (data->map[map_pos] != 1)
		return (false);
	return (true);
}

void	normalize_angle(float *angle, float increment)
{
	*angle += increment;
	if (*angle < 0)
		*angle += 2 * PI;
	else if (*angle > 2 * PI)
		*angle -= 2 * PI;
}

float	dist(t_line line)
{
	return (sqrt((line.x1 - line.x0) * (line.x1 - line.x0)
			+ (line.y1 - line.y0) * (line.y1 - line.y0)));
}

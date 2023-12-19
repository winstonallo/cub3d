/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:35:02 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/17 20:18:22 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	print_test(t_data *data, int color, int value, int x, int y){
	if (x*y>data->map_height*data->map_width)
		printf("x/y max value exceeded\n");
	if ((value == 1 && color != data->wall_color) || (value == 0 && color != data->floor_color)){
		printf("wrong color\n");
		printf("map value: [%d]", value);
		printf("color value: [%d]\n", color);
	}
	else{
		printf("map coordinates: x:[%d] -- y:[%d]\n", x, y);
		printf("map value: [%2d]", value);
		printf("                                  ✅\n");
	}
}

int	print_test_raycasting(t_data *data, int loopbreak, int direction, t_raycast *ray){
	printf(BOLD);
	if(!loopbreak){}
	// 	return (printf("Player Coordinates:     x: %d | y: %d\n", ray->map_x, ray->map_y));
	printf(RED);
	if (data->map[ray->map_pos] != 1)
		printf("\n--- ERROR ---\n\n");
	else{
		printf(RESET);
		printf(CURSIVE);
		if (direction == HORIZONTAL){
			printf(GREEN);
			printf("--horizontal-ray--\n");
		}
		else{
			printf(YELLOW);
			printf("--vertical-ray--\n");
		}
		printf(RESET);
		printf(BOLD);
		printf(RED);
		printf("\n--- HIT WALL ---\n\n");
	}
	printf(RESET);
	printf("map value:              ");
	if (data->map[ray->map_pos])
		printf("✅");
	printf("\nhit position on map:    x: %5d | y: %5d  | mp: %d\n", ray->map_x, ray->map_y, ray->map_pos);
	printf("hit position on screen: x: %5d | y: %5d\n", (int)ray->reach_x, (int)ray->reach_y);
	printf("player on screen:       x: %5d | y: %5d\n", (int)data->player.x_pos, (int)data->player.y_pos);
	printf("current angle:          r: %5f", ray->angle);
	printf("\n-----------------------------------\n\n");
	return (0);
}

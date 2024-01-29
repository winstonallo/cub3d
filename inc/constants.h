/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:19:30 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/29 17:06:11 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define PI 3.1415926535
# define P2 1.570796327
# define P3 4.71238898
# define MAX_DISTANCE 1000
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000
# define SCREEN_HEIGHT2 500
# define SPEED 0.03
# define TURN_SPEED 10
# define DR 0.00872665
# define MAX_DIST 1000000
# define WALL_HEIGHT 1.2
# define COLL_SENS 0.15
# define SOME_LARGE_VALUE 1000000
# define SCALE 125.0
# define FOV_INCREMENT 1.04719755
# define FOV 120
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'
# define NEWLINE '\n'

# define ESCAPE 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define Q 113

typedef enum s_scale
{
	MAPSIZE,
	SCREEN
}	t_scale;

typedef enum s_ray
{
	VERTICAL,
	HORIZONTAL
}	t_ray;

typedef enum s_move
{
	DOWN,
	UP,
	TURN_LEFT,
	TURN_RIGHT,
	STRAFE_RIGHT,
	STRAFE_LEFT
}	t_move;

typedef enum s_error
{
	SUCCESS,
	NO_WALL_HIT
}	t_error;

typedef enum s_color
{
	CEILING,
	FLOOR
}	t_color;

#endif
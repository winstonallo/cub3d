/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:33:43 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/21 12:47:14 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

int	isdirection(char c)
{
	if (c == 'N')
		return (NORTH);
	else if (c == 'S')
		return (SOUTH);
	else if (c == 'E')
		return (EAST);
	else if (c == 'W')
		return (WEST);
	return (0);
}

void	set_directions(t_data *data)
{
	if (data->view_dir == NORTH)
	{
		data->player.y_dir = 1;
		data->player.x_dir = 0;
	}
	else if (data->view_dir == SOUTH)
	{
		data->player.y_dir = -1;
		data->player.x_dir = 0;
	}
	else if (data->view_dir == EAST)
	{
		data->player.y_dir = 0;
		data->player.x_dir = 1;
	}
	else if (data->view_dir == WEST)
	{
		data->player.y_dir = 0;
		data->player.x_dir = -1;
	}
}

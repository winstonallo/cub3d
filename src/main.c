/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:49:33 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 16:15:21 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"
#include <stdlib.h>

void	textures_pointers_init(t_data *data)
{
	data->ea_txtr = NULL;
	data->we_txtr = NULL;
	data->so_txtr = NULL;
	data->no_txtr = NULL;
}

int	main(int argc, char **argv)
{
	t_data	data;

	check_argument_count(argc);
	textures_pointers_init(&data);
	data.map = map(argv[1], &data);
	if (!data.map)
	{
		free_textures(&data);
		exit(EXIT_FAILURE);
	}
	data_init(&data);
	start_game(&data);
	return (0);
}

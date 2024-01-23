/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:49:33 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/23 21:29:22 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_data	data;
	int		maps;

	if (argc < 2)
		return (perror("Error\nWrong format. Use: ./cub3d [mapnames, ...]"), 1);
	else if (argc > 3)
		return (perror("Error\nTo many maps loaded. Max size is one"), 1);
	data.maps = (int **)malloc(sizeof(int *) * (argc - 1));
	if (!data.maps)
		return (perror("Error\nAllocation failed in main"), 1);
	maps = -1;
	while (++maps < argc - 1)
	{
		data.maps[maps] = map(argv[1 + maps], &data);
		if (!data.maps[maps])
		{
			while (--maps >= 0)
				free(data.maps[maps]);
			return (free(data.maps), perror("Error\nMap failed to load"), 1);
		}
	}
	// (void)maps;
	// (void)argc;
	// data.map = map(argv[1]);
	// data.map = data.maps[0];
	// int map[] = {1, 1, 1, 1, 1, -1, -1, -1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 89, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, -2};
	// (void)map;
	data.map = data.maps[0];
	data.argc = argc - 2;
	data_init(&data, argc);
	start_game(&data);
	free(data.maps[0]);
	free(data.maps);
	return (0);
}

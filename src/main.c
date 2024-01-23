/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:49:33 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/23 22:08:53 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"
#include <stdlib.h>

static void	check_argument_count(int argc)
{
	if (argc < 2)
	{
		ft_putstr_fd("Error\nWrong format. Use: ./cub3d [mapnames]\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (argc > 3)
	{
		ft_putstr_fd("Error\nToo many maps (max 1)\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		maps;

	check_argument_count(argc);
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
	data.map = data.maps[0];
	data.argc = argc - 2;
	data_init(&data);
	start_game(&data);
	free(data.maps[0]);
	free(data.maps);
	return (0);
}

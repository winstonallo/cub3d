/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:49:33 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 15:20:02 by abied-ch         ###   ########.fr       */
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

	check_argument_count(argc);
	data.map = map(argv[1], &data);
	if (!data.map)
		exit(EXIT_FAILURE);
	data_init(&data);
	start_game(&data);
	return (0);
}

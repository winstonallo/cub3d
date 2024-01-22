/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:49:33 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/22 17:11:23 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"
#include <stdlib.h>

int	main(void)
{
	t_data	data;

	data.map = map("wow.cub");
	if (!data.map)
		return (EXIT_FAILURE);
	data_init(&data);
	start_game(&data);
	return (0);
}

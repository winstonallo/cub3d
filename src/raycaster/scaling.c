/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:19:43 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/23 23:13:37 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

static void	high_values_init(double **scaling)
{
	(*scaling)[26] = 4.81;
	(*scaling)[27] = 4.63;
	(*scaling)[28] = 4.46;
	(*scaling)[29] = 4.31;
	(*scaling)[30] = 4.17;
	(*scaling)[31] = 4.03;
	(*scaling)[32] = 3.91;
	(*scaling)[33] = 3.79;
	(*scaling)[34] = 3.68;
	(*scaling)[35] = 3.57;
	(*scaling)[36] = 3.47;
	(*scaling)[37] = 3.38;
	(*scaling)[38] = 3.29;
	(*scaling)[39] = 3.21;
	(*scaling)[40] = 3.13;
	(*scaling)[41] = 3.05;
	(*scaling)[42] = 2.98;
	(*scaling)[43] = 2.91;
	(*scaling)[44] = 2.84;
	(*scaling)[45] = 2.78;
	(*scaling)[46] = 2.72;
	(*scaling)[47] = 2.66;
	(*scaling)[48] = 2.6;
	(*scaling)[49] = 2.55;
	(*scaling)[50] = 2.5;
}

static void	scale_array_init(double **scaling)
{
	(*scaling)[3] = 41.67;
	(*scaling)[4] = 31.25;
	(*scaling)[5] = 25;
	(*scaling)[6] = 21;
	(*scaling)[7] = 17.87;
	(*scaling)[8] = 15.62;
	(*scaling)[9] = 13.89;
	(*scaling)[10] = 12.5;
	(*scaling)[11] = 11.36;
	(*scaling)[12] = 10.42;
	(*scaling)[13] = 9.61;
	(*scaling)[14] = 8.93;
	(*scaling)[15] = 8.33;
	(*scaling)[16] = 7.81;
	(*scaling)[17] = 7.35;
	(*scaling)[18] = 6.94;
	(*scaling)[19] = 6.58;
	(*scaling)[20] = 6.25;
	(*scaling)[21] = 5.95;
	(*scaling)[22] = 5.68;
	(*scaling)[23] = 5.43;
	(*scaling)[24] = 5.21;
	(*scaling)[25] = 5;
	high_values_init(scaling);
}

void	set_wall_scaling_factor(t_data *data)
{
	double	*scaling;

	scaling = (double *)ft_calloc(sizeof(double), 51);
	if (!scaling)
		exit_failure(data, "Error\nAllocation failed in set_wall_scaling_factor");
	scale_array_init(&scaling);
	data->scaling = scaling[data->map_width];
}

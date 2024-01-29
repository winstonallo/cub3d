/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:19:43 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 19:07:16 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"
#include <assert.h>

static void	high_init(double **scaling)
{
	(*scaling)[76] = 1.6445;
	(*scaling)[77] = 1.625;
	(*scaling)[78] = 1.605;
	(*scaling)[79] = 1.582;
	(*scaling)[80] = 1.562;
	(*scaling)[81] = 1.543;
	(*scaling)[82] = 1.525;
	(*scaling)[83] = 1.507;
	(*scaling)[84] = 1.49;
	(*scaling)[85] = 1.473;
	(*scaling)[86] = 1.456;
	(*scaling)[87] = 1.44;
	(*scaling)[88] = 1.42;
	(*scaling)[89] = 1.405;
	(*scaling)[90] = 1.388;
	(*scaling)[91] = 1.375;
	(*scaling)[92] = 1.36;
	(*scaling)[93] = 1.345;
	(*scaling)[94] = 1.33;
	(*scaling)[95] = 1.315;
	(*scaling)[96] = 1.301;
	(*scaling)[97] = 1.288;
	(*scaling)[98] = 1.275;
	(*scaling)[99] = 1.262;
	(*scaling)[100] = 1.25;
}

static void	mid_high_init(double **scaling)
{
	(*scaling)[52] = 2.4;
	(*scaling)[53] = 2.35;
	(*scaling)[54] = 2.31;
	(*scaling)[55] = 2.27;
	(*scaling)[56] = 2.23;
	(*scaling)[57] = 2.19;
	(*scaling)[58] = 2.15;
	(*scaling)[59] = 2.12;
	(*scaling)[60] = 2.085;
	(*scaling)[61] = 2.05;
	(*scaling)[62] = 2.018;
	(*scaling)[63] = 1.986;
	(*scaling)[64] = 1.955;
	(*scaling)[65] = 1.925;
	(*scaling)[66] = 1.896;
	(*scaling)[67] = 1.868;
	(*scaling)[68] = 1.84;
	(*scaling)[69] = 1.813;
	(*scaling)[70] = 1.786;
	(*scaling)[71] = 1.76;
	(*scaling)[72] = 1.738;
	(*scaling)[73] = 1.716;
	(*scaling)[74] = 1.694;
	(*scaling)[75] = 1.668;
	high_init(scaling);
}

static void	mid_init(double **scaling)
{
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
	(*scaling)[51] = 2.45;
	mid_high_init(scaling);
}

static void	scale_array_init(double **scaling)
{
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
	(*scaling)[26] = 4.81;
	(*scaling)[27] = 4.63;
	mid_init(scaling);
}

void	set_map_scale(t_data *data)
{
	double	*scaling;

	if (data->map_width > 100)
		exit_error("Map too big", data);
	if (data->map_width < 3)
		exit_error("Map too small", data);
	set_scaling_factor(data);
	scaling = (double *)ft_calloc(sizeof(double), 101);
	if (!scaling)
		exit_failure(data, "Error\nMalloc failure in set_wall_scaling_factor");
	scaling[3] = 41.67;
	scale_array_init(&scaling);
	data->scaling = scaling[data->map_width];
	free(scaling);
}

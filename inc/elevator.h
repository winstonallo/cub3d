/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 00:54:07 by yannis            #+#    #+#             */
/*   Updated: 2024/01/22 17:59:12 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEVATOR_H
# define ELEVATOR_H

# define _POSIX_C_SOURCE 199309L

# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/include/libft.h"
# include "raycast_structs.h"

void	gif_delete(t_data *game, void *mlx);
void	change_floor(t_data *data);
void	lift_switch(t_data *data);
int		gif_init(t_data *game, char *path, int posx, int posy);

#endif

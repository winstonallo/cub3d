/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:46:06 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/22 17:59:07 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTON_H
# define BUTTON_H

# define _POSIX_C_SOURCE 199309L

# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>
# include <mlx.h>
# include <stdlib.h>
# include "../libft/include/libft.h"
# include "raycast_structs.h"

int			button_init_master(t_data *game, char *path, int (*f)(t_data *, int));
void		b_matrix_free(char **arr);
void		display_button(t_data *game, int i, int lap, int inc);
void		button_delete_master(t_data *game, void *mlx);
int			load_button(t_button *button, void *mlx, char *path);
int			button_add_function_master(int (*function)(t_data *, int), t_data *game, int i);
int			button_change_position_master(t_data *game, int posx, int posy, int iden);
int			button_animation_master(void *data);
int			button_switch_master(t_data *game, int i);
int			mouse_actions(int (*function)(t_data *, int i), t_data *game, int i);

void		free_game(t_data *game);

#endif

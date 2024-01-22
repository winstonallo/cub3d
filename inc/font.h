/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:01:25 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/22 17:59:14 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <stdbool.h>
# include <fcntl.h>
# include "../libft/include/libft.h"
# include "raycast_structs.h"

// font init functions //
t_font	*font_init_master(void *mlx);
int		load_font(void *mlx, t_font *font, char **names);

// font write functions //
int		font_write_master(char *w, t_data *game, t_font_setting f);
int		font_write_to_im_master(char *w, t_data *g, t_txtr *c, t_font_setting s);
void	font_to_lower(char *word);
void	*font_create_new_image(char *word, t_data *game, int identifier);
void	font_write_to_image(t_data *ga, t_txtr *t, char *to, t_font_setting fo);
void	font_write_to_display(t_data *ga, char *to, t_font_setting fo);
void	free_array(char **name);

// font helper functins //
void	del_font(void *mlx, t_font *font, int type);
void	save_quit_extend(void *mlx, t_font *font, int err_code, int filter);
void	save_quit(void *mlx, t_font *font, int err_code, int filter);
void	font_free_images(t_font *font, int i);

// image edit functions //
void	image_edit(t_data *game, t_txtr *base, t_txtr to_copy, int identifier);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gif.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 00:33:55 by yannis            #+#    #+#             */
/*   Updated: 2024/01/22 17:59:24 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GIF_H
# define GIF_H

# define _POSIX_C_SOURCE 199309L

# include <time.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include "../libft/include/libft.h"
# include "raycast_structs.h"

void	raycast(t_data *data);
void	image_edit(t_data *g, t_txtr *base, t_txtr to_copy, int identifier);
void	free_images(t_gif *gif, void *mlx, int amount);
int		identify_amount(char *path);
int		alloc_imgs(t_gif *gif, char *path, void *mlx);

#endif

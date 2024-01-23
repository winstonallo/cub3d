/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:47:40 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/23 21:09:01 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "../libft/include/libft.h"
# include "raycast_structs.h"

typedef struct s_texture
{
	char	*color_fds[2];
	int		texture_fds[4];
	int		err_code;
}				t_texture;

int			*map(char *map, t_data *data);
int			map_get_player_pos(int *map);
t_texture	map_get_txtrs(char *map);
int			replace(char *fname, char *pos, char *content);

#endif
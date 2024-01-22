/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:38:48 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/22 18:01:58 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../libft/include/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include "cub3d.h"
# include "raycast_structs.h"

// Check if functions //
char	*load_map(int fd);
int		check_if_exists(char *map);
int		check_if_valid(char *map);

// Check if helper functions //
char	**fill_params(int flag);
int		check_if_all_textures_helper(char **params, char **err, char *map);
int		check_for(t_check *check, char *map, char **tags, int pos);

// General helper functions //
void	m_matrix_free(char **error_names);
char	*load_map(int fd);
char	*str_join_block(char *str, char *str_temp);
char	*copy(char *to_copy, int size);
int		skip_whitespaces(char *str, int pos);
int		validate_file(char *str, int valid, char **error, int pos);
int		validate_rgb(char *str, int valid, char **error, int pos);
int		check_if_rgb_correct(char *str);

// Map functions //
char	*map_valid(char *loaded);
int		*slice_map(char *map);

// Map valid helper functions //
char	*fixed(char *origin);
char	*remove_nls(char *updated);
int		*slicer(char *map);
int		check_map_if_valid(char *map);
int		check_player_in_map(char *map);
int		*map_main(char *map);

#endif

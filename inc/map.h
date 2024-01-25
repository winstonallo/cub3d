/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:38:48 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 18:05:08 by abied-ch         ###   ########.fr       */
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

typedef struct s_fixed_struct
{
	char	*str;
	int		box_size;
	int		index;
	int		pos;
	int		line;
	int		ll;
}				t_fixed_struct;

// Check if functions //
char	*load_map(int fd);
int		check_if_exists(char *map);
int		check_if_valid(char *map, t_data *data);

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
int		validate_file(t_check *check, t_data *data);
int		validate_rgb(char *str, int valid, t_data *data, int ident);
int		check_if_rgb_correct(char *str, t_data *data, int ident);
int		skip(char *map);
int		len(char *str);

// Map functions //
char	*map_valid(char *loaded, t_data *data);
int		*slice_map(char *map, t_data *data);
int		mpl(char *map);

// Map valid helper functions //
char	*true_size(char *map, int height);
char	*fixed(char *origin);
char	*remove_nls(char *updated);
int		*slicer(char *map);
int		check_map_if_valid(char *map, int i, int leaks);
int		check_player_in_map(char *map);
int		*map_main(char *map, t_data *data);
int		line_len(char *map);
int		longest_line(char *map, int height);
int		after(char *map, int line);
int		before(char *map, int height);

#endif
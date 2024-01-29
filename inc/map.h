/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:38:48 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 19:07:21 by yatabay          ###   ########.fr       */
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
# include "raycast.h"

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
bool	check_if_exists(char *map);
int		check_if_valid(char *map, t_data *data, int *nl);
char	*check_only_spaces(char *map);

// Check if helper functions //
char	**fill_params(int flag);
int		check_if_all_textures_helper(char **params, char *map, int *nl);
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
int		*slice_map(char *map, t_data *data, int *nl);
int		mpl(char *map);
void	error(char *str);

// Map valid helper functions //
int		check_substring(char *s, int *passed, int *pos, int comma);
int		check_code_order(char *s);
int		count_commas(char *s);
void	get_color(char **rgb, t_data *data, int ident);
char	*true_size(char *map, int height);
int		len_till_space(char *str);
char	*fixed(char *origin);
char	*remove_nls(char *updated);
int		*slicer(char *map);
int		check_map_if_valid(char *map, int i, int leaks, int newline);
int		check_player_in_map(char *map);
int		*map_main(char *map, t_data *data);
int		line_len(char *map);
int		longest_line(char *map, int height);
int		after(char *map, int line);
int		before(char *map, int height);
int		check_before_split(char *s, int pos, int passed);

#endif
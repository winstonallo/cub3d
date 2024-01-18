/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:39:18 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/18 03:17:18 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

// Util functions
int		replace_value(char *fname, char *map, char *identifier, char *content);
int		input(char *fname, char *pos, char *content);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:57:35 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/14 22:07:22 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "../../../libft/libft.h"

// Util functions
int		replace_value(char *fname, char *map, char *identifier, char *content);
int		input(char *fname, char *pos, char *content);

#endif

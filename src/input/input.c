/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:03:43 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/14 22:09:53 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	input(char *fname, char *pos, char *content);

int	replace(char *fname, char *pos, char *content)
{
	return (input(fname, pos, content) < 0);
}

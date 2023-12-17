/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:45:23 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/17 12:45:36 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/input.h"

int	input(char *fname, char *pos, char *content);

int	replace(char *fname, char *pos, char *content)
{
	return (input(fname, pos, content) < 0);
}
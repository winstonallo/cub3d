/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:42:17 by yannis            #+#    #+#             */
/*   Updated: 2023/12/25 21:10:08 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

int	int_exit(t_temp *temp, int i)
{
	int	pos;

	pos = 0;
	(void)i;
	while (pos < temp->button_index)
		button_delete(temp->button[pos++], temp->mlx);
	free(temp->button);
	free_game(temp);
	exit(0);
	return (0);
}

int	say(t_temp *temp, int i)
{
	(void)temp;
	(void)i;
	write(1, "Hi. I got clicked\n", 18);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:42:17 by yannis            #+#    #+#             */
/*   Updated: 2024/01/08 00:57:52 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

int	int_exit_master(t_game *temp, int i)
{
	int	pos;

	pos = 0;
	(void)i;
	while (pos < temp->button_index)
		button_delete_master(temp, temp->mlx);
	free(temp->button);
	free_game(temp);
	exit(0);
	return (0);
}

int	say_master(t_game *temp, int i)
{
	(void)temp;
	(void)i;
	write(1, "Hi. I got clicked\n", 18);
	return (0);
}
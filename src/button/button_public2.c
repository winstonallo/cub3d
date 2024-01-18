/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_public2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 00:08:31 by yannis            #+#    #+#             */
/*   Updated: 2024/01/18 03:24:07 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

int	int_exit_master(t_data *temp, int i);
int	say_master(t_data *temp, int i);

int int_exit(t_data *game, int i)
{
	return (int_exit_master(game, i));
}

int	say(t_data *temp, int i)
{
	return (say_master(temp, i));
}
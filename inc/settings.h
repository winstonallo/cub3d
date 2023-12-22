/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:21:32 by arthur            #+#    #+#             */
/*   Updated: 2023/12/22 09:03:09 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

#include "cub3d.h"

void	exit_failure(t_data *data, char *msg);

void	settings(t_data *data, char *file);

#endif
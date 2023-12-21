/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:21:32 by arthur            #+#    #+#             */
/*   Updated: 2023/12/21 19:26:45 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include "cub3d.h"

typedef struct s_settings
{
    int     screen_width;
    int     screen_height;
    int     minimap_size;
    int     field_of_view;
    float   speed;
    int		turn_speed;
}   t_settings;

#endif
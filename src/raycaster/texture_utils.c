/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:31:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/21 11:32:59 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

int	get_pixel(t_texture *texture, int x, int y)
{
	int		color;
	char	*dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x000000);
	dst = texture->addr + (y * texture->l_l + x * (texture->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void draw_texture(t_data *data, int x, t_line line, t_texture *texture) {
    int color;
    int y;
    int texture_y;
    int screen_y;
    int texture_x;
    float texture_pct;

    // Loop over each pixel in the column
    y = -1;
    while (++y < line.wall_height) {
        texture_pct = (float)y / (float)line.wall_height;
        texture_y = (int)(texture_pct * texture->height) % texture->height;

        // Calculate the texture_x based on the hit position on the wall
        // 'hit_position' should be a normalized value [0, 1] representing
        // the position of the hit along the wall from one end to the other.
        texture_x = (int)(data->hit_pos * (float)texture->width) % texture->width;

        // Fetch the color from the texture at texture_x, texture_y
        color = get_pixel(texture, texture_x, texture_y);

        screen_y = line.y0 + y;
        if (screen_y >= 0 && screen_y < SCREEN_HEIGHT) {
            put_pixel(data, x, screen_y, color);
        }
    }
}


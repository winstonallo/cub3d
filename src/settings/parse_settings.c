/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:26:01 by arthur            #+#    #+#             */
/*   Updated: 2023/12/22 14:09:48 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/settings.h"

void	store_settings(char *line, t_data *data, int i)
{
	if (i == 1)
		data->settings.screen_width = ft_atoi(line);
	else if (i == 2)
		data->settings.screen_height = ft_atoi(line);
	else if (i == 3)
		data->settings.minimap_size = ft_atoi(line);
	else if (i == 4)
		data->settings.field_of_view = ft_atoi(line);
	else if (i == 5)
    	data->settings.speed = ft_atof(line);
	else if (i == 6)
        data->settings.turn_speed = ft_atoi(line);
	
}

void    read_settings_file(char *file, t_data *data)
{
    char    *line;
    int     fd;
    int		status;
	int     i;

	i = 0;
	status = 1;
    fd = open(file, O_RDONLY);
	if (fd < 0)
		return (exit_failure(data, "Error\ncould not open settings file"));
    while (status && ++i)
    {
		status = get_next_line(fd, &line);
		if (status == -1)
		{
			perror("Error\nsettings set to default");
			break ;
		}
		store_settings(line, data, i);
    }
    freeze(line);
    close(fd);
}

void	settings(t_data *data, char *file)
{
	read_settings_file(file, data);
}

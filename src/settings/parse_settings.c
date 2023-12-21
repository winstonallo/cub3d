/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:26:01 by arthur            #+#    #+#             */
/*   Updated: 2023/12/21 20:03:29 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/settings.h"

void	store_settings(char *line, t_data *data, int i)
{
	
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

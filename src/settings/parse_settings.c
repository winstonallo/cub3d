/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:26:01 by arthur            #+#    #+#             */
/*   Updated: 2023/12/21 19:34:01 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/settings.h"

void    read_settings_file(char *file)
{
    char    *line;
    int     fd;
    int		status;

	status = 1;
    fd = open(file, O_RDONLY);
    while (status)
    {
		status = get_next_line(fd, &line);
		if (status == -1)
			break ;
        printf("%s\n", line);
        free(line);
    }
    free(line);
    close(fd);
}

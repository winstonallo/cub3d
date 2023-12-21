/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:45:38 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/21 12:27:31 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/input.h"

static	char	*str_join_block(char *str, char *str_temp)
{
	char	*temp;
	char	*map;

	temp = ft_strjoin(str, str_temp);
	free(str);
	if (!temp)
		return (printf("Allocation temp failed"), NULL);
	map = ft_strjoin(temp, "");
	free(temp);
	if (!map)
		return (printf("Allocation map failed"), NULL);
	return (map);
}

char	*load_map2(int fd)
{
	char	*map;
	char	*t_char;
	int		single;

	map = (char *)malloc(sizeof(char) * 1);
	if (!map)
		return (printf("Allocation in load_map failed\n"), NULL);
	map[0] = 0;
	while (1)
	{
		single = 0;
		(void)read(fd, &single, 1);
		if (single < 32 && single != '\n')
			break ;
		t_char = malloc(2);
		if (!t_char)
			return (printf("Error\nAllocation t_char failed\n"), NULL);
		t_char[0] = single;
		t_char[1] = 0;
		map = str_join_block(map, t_char);
		if (!map)
			return (free(t_char), printf("Error\nstr_join alloc fail\n"), NULL);
		free(t_char);
	}
	printf("map: %s\n", map);
	return (map);
}

static	int	replace_main(char *fname, int fd, char *pos, char *content)
{
	char	*map;

	map = load_map2(fd);
	if (!map)
		return (-1);
	if (ft_strnstr(map, pos, ft_strlen(map)))
	{
		if (replace_value(fname, map, pos, content) < 0)
			return (free(map), -1);
	}
	free(map);
	return (0);
}

int	input(char *fname, char *pos, char *content)
{
	int	fd;

	if ((!(pos[0] == 'N' && pos[1] == 'O' && pos[2] == 0))
		&& (!(pos[0] == 'S' && pos[1] == 'O' && pos[2] == 0))
		&& (!(pos[0] == 'W' && pos[1] == 'E' && pos[2] == 0))
		&& (!(pos[0] == 'E' && pos[1] == 'A' && pos[2] == 0))
		&& (!(pos[0] == 'F' && pos[1] == 0))
		&& (!(pos[0] == 'C' && pos[1] == 0)))
		return (printf("Error\nFile-Identifier unknown\n"), -1);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nFile is not a valid one\n"), -1);
	if (replace_main(fname, fd, pos, content) < 0)
		return (close(fd), -1);
	close(fd);
	return (0);
}

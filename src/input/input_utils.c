/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:46:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/17 12:46:24 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/input.h"

static	int	diff(char *map, char *identifier)
{
	char	*temp;
	int		i;
	int		j;

	temp = ft_strdup(ft_strnstr(map, identifier, ft_strlen(map)));
	if (!temp)
		return (printf("Error\nAllocation failed in replace_value\n"), -1);
	j = 0;
	i = 0;
	while (temp[j])
		j++;
	i = (int)ft_strlen(map) - j;
	free(temp);
	return (i);
}

static	int	identify_new_line(char *map, int *diffrence)
{
	int	current_pos;
	int	line;

	current_pos = 0;
	line = 0;
	while (map[current_pos])
	{
		if (map[current_pos] == '\n')
			line++;
		if (*diffrence == current_pos)
			break ;
		current_pos++;
	}
	*diffrence = 0;
	return (line);
}

static	void	insert(char *new, char *map, char *identifier, char *content)
{
	int	inner;
	int	i;
	int	j;

	i = ft_strlen(new) - 1;
	j = ft_strlen(new) - 1;
	while (map[j] != '\n')
		j++;
	inner = 0;
	while (identifier[inner])
		new[i++] = identifier[inner++];
	new[i++] = 32;
	inner = 0;
	while (content[inner])
		new[i++] = content[inner++];
	while (map[j])
		new[i++] = map[j++];
	new[i++] = 0;
}

static	int	write_file(char *fname, char *new)
{
	int	loop;
	int	new_fd;

	new_fd = open(fname, O_RDWR);
	if (new_fd < 0)
		return (printf("Error\nCant open file\n"), free(new), -1);
	loop = 0;
	while (new[loop])
		write(new_fd, &new[loop++], 1);
	free(new);
	close(new_fd);
	return (0);
}

int	replace_value(char *fname, char *map, char *identifier, char *content)
{
	char	*new;
	int		pos;
	int		diffrence;
	int		line;

	new = (char *)malloc(ft_strlen(map) + ft_strlen(content) + 1);
	if (!new)
		return (printf("Error\nAllocation failed in replace_value\n"), -1);
	diffrence = diff(map, identifier);
	if (diffrence < 0)
		return (free(new), -1);
	line = identify_new_line(map, &diffrence);
	pos = -1;
	while (map[++pos] && diffrence < line)
	{
		new[pos] = map[pos];
		if (map[pos] == '\n')
			diffrence++;
	}
	new[pos] = map[pos];
	new[++pos] = 0;
	insert(new, map, identifier, content);
	if (write_file(fname, new) < 0)
		return (-1);
	return (0);
}

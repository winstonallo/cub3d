/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:43:02 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 19:12:36 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"

int	new_lines(char *map);

char	*check_only_spaces(char *map)
{
	int	error;
	int	pos;

	pos = -1;
	error = 1;
	while (map[++pos])
	{
		if (map[pos] != 32 && map[pos] != 10)
			error = 0;
	}
	if (error != 0)
		return (free(map), ft_putstr_fd("Error\nFile empty\n", 2), NULL);
	return (map);
}

char	*remove_nls_subpart(char *updated, int nls)
{
	char	*sub;
	int		pos;
	int		nl;

	sub = (char *)malloc(ft_strlen(updated) + 1);
	if (!sub)
		return (free(updated), perror("Error\nAllocation failed"), NULL);
	pos = 0;
	nl = 0;
	while (updated[pos])
	{
		if (updated[pos] == '\n')
		{
			nl++;
			if (nl == nls)
				break ;
		}
		pos++;
	}
	nl = 0;
	while (updated[pos])
		sub[nl++] = updated[++pos];
	sub[nl] = 0;
	free(updated);
	return (sub);
}

char	*remove_nls(char *updated)
{
	char	*new;
	int		runner;
	int		nl;

	runner = 0;
	nl = 0;
	while (updated[runner] && (updated[runner] == 0
			|| updated[runner] == 32 || updated[runner] == 10))
	{
		if (updated[runner] == 10)
			nl++;
		runner++;
	}
	new = remove_nls_subpart(updated, nl);
	if (!new)
		return (perror("Error\nAlloc failed in remove_nls"), NULL);
	return (new);
}

int	*slicer(char *map)
{
	int	*arr;
	int	pos;
	int	i;

	i = -1;
	pos = 0;
	arr = (int *)malloc(sizeof(int) * ft_strlen(map));
	if (!arr)
		return (perror("Error\nAllocation failed"), NULL);
	while (map[++i])
	{
		if (map[i] == ' ')
			arr[pos++] = -1;
		if (map[i] == '1')
			arr[pos++] = 1;
		if (map[i] == 'X')
			arr[pos++] = 0;
		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'W' || map[i] == 'E')
			arr[pos++] = 2 + map[i];
	}
	arr[pos] = -2;
	return (arr);
}

int	*map_main(char *map, t_data *data)
{
	int	*sliced_map;
	int	nl;

	if (check_if_exists(map) == false)
		return (NULL);
	if (check_if_valid(map, data, &nl) < 0)
		return (NULL);
	sliced_map = slice_map(map, data, &nl);
	if (!sliced_map)
		return (NULL);
	return (sliced_map);
}

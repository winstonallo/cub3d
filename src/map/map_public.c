/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_public.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:42:09 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/14 15:13:40 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	mpl(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

int	map_get_player(int *map)
{
	int	i;

	i = 0;
	while (map[i] != -2)
	{
		if (map[i] > 2)
			break ;
		i++;
	}
	return (i);
}

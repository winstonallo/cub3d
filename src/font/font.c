/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:11:49 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/19 23:36:35 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static	char	**font_names(void)
{
	char	**names;
	char	*joined;
	char	*temp;

	temp = ft_strdup("a.xpm,b.xpm,c.xpm,d.xpm,e.xpm,f.xpm,g.xpm,h.xpm,i.xpm,");
	if (!temp)
		return (printf("Error\nAlloc failed in font_name: T0"), NULL);
	joined = ft_strjoin(temp, "j.xpm,k.xpm,l.xpm,m.xpm,n.xpm,o.xpm,p.xpm,");
	free(temp);
	if (!temp)
		return (printf("Error\nAlloc failed in font_name: J0"), NULL);
	temp = ft_strjoin(joined, "q.xpm,r.xpm,s.xpm,t.xpm,u.xpm,v.xpm,w.xpm,");
	free(joined);
	if (!temp)
		return (printf("Error\nAlloc failed in font_name: T1"), NULL);
	joined = ft_strjoin(temp, "x.xpm,y.xpm,z.xpm");
	free(temp);
	if (!joined)
		return (printf("Error\nAlloc failed in font_name: J1"), NULL);
	names = ft_split(joined, ',');
	free(joined);
	if (!names)
		return (printf("Error\nAlloc failed in font_name"), NULL);
	return (names);
}

static	int	all_clear(char **names, char *path)
{
	char	*str;
	int		pos;
	int		fd;

	pos = 0;
	while (names[pos])
	{
		str = ft_strjoin(path, names[pos]);
		if (!str)
			return (printf("Error\nAlloc failed in all_clear\n"), -1);
		fd = open(str, O_RDONLY);
		if (fd < 0)
			return (printf("Error\nFile %s missing\n", names[pos]),
				free(str), -1);
		close(fd);
		free(str);
		pos++;
	}
	return (0);
}

t_font	*font_init(void *mlx)
{
	t_font	*font;
	char	**names;

	font = (t_font *)malloc(sizeof(t_font));
	if (!font)
		return (printf("Error\nAlloc failed in font_init\n"), NULL);
	names = font_names();
	if (!names)
		return (free(font), NULL);
	if (all_clear(names, "src/font/fonts/xl_font/") < 0)
		return (free_array(names), free(font), NULL);
	if (all_clear(names, "src/font/fonts/big_font/") < 0)
		return (free_array(names), free(font), NULL);
	if (all_clear(names, "src/font/fonts/medium_font/") < 0)
		return (free_array(names), free(font), NULL);
	if (all_clear(names, "src/font/fonts/small_font/") < 0)
		return (free_array(names), free(font), NULL);
	if (load_font(mlx, font, names) < 0)
		return (write(1, "wow\n", 4), NULL);
	free_array(names);
	return (font);
}

int	font_write(char *word, t_game *game, t_img *copy, int identifier)
{
	char	*to_write;

	to_write = ft_strdup(word);
	if (!to_write)
		return (printf("Error\nAlloc failed in font_write\n"), -1);
	font_to_lower(to_write);
	font_write_to_image(game, copy, to_write, identifier);
	free(to_write);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:12:56 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/18 01:48:18 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/font.h"

static	int	open_small_images(void *mlx, t_font *font, char **names)
{
	char	*name;
	void	*img;
	int		i;

	i = -1;
	font->small_font.letter = (t_img *)malloc(sizeof(t_img) * 26);
	if (!font->small_font.letter)
		return (printf("Error\nAlloc failed in o_x_l_img\n"), -1);
	while (++i < 26)
	{
		name = ft_strjoin("src/font/fonts/small_font/", names[i]);
		if (!name)
			return (printf("Error\nAlloc failed in o_x_l_img\n"), -2);
		img = mlx_xpm_file_to_image(mlx, name,
				&(font->small_font.letter[i].width),
				&(font->small_font.letter[i].height));
		font->small_font.letter[i].img = img;
		font->small_font.del++;
		free(name);
		if (!font->small_font.letter[i].img)
			return (printf("Error\nAlloc failed in o_xl_i, img [%i]\n", i),
				font_free_images(font, i), free(font->small_font.letter), -3);
	}
	return (0);
}

static	int	open_medium_images(void *mlx, t_font *font, char **names)
{
	char	*name;
	void	*img;
	int		i;

	i = -1;
	font->medium_font.letter = (t_img *)malloc(sizeof(t_img) * 26);
	if (!font->medium_font.letter)
		return (printf("Error\nAlloc failed in o_x_l_img\n"), -1);
	while (++i < 26)
	{
		name = ft_strjoin("src/font/fonts/medium_font/", names[i]);
		if (!name)
			return (printf("Error\nAlloc failed in o_x_l_img\n"), -2);
		img = mlx_xpm_file_to_image(mlx, name,
				&(font->medium_font.letter[i].width),
				&(font->medium_font.letter[i].height));
		font->medium_font.letter[i].img = img;
		font->medium_font.del++;
		free(name);
		if (!font->medium_font.letter[i].img)
			return (printf("Error\nAlloc failed in o_xl_i, img [%i]\n", i),
				font_free_images(font, i), free(font->medium_font.letter), -3);
	}
	return (0);
}

static	int	open_big_images(void *mlx, t_font *font, char **names)
{
	char	*name;
	void	*img;
	int		i;

	i = -1;
	font->big_font.letter = (t_img *)malloc(sizeof(t_img) * 26);
	if (!font->big_font.letter)
		return (printf("Error\nAlloc failed in o_x_l_img\n"), -1);
	while (++i < 26)
	{
		name = ft_strjoin("src/font/fonts/big_font/", names[i]);
		if (!name)
			return (printf("Error\nAlloc failed in o_x_l_img\n"), -2);
		img = mlx_xpm_file_to_image(mlx, name,
				&(font->big_font.letter[i].width),
				&(font->big_font.letter[i].height));
		font->big_font.letter[i].img = img;
		font->big_font.del++;
		free(name);
		if (!font->big_font.letter[i].img)
			return (printf("Error\nAlloc failed in o_xl_i, img [%i]\n", i),
				font_free_images(font, i), free(font->big_font.letter), -2);
	}
	return (0);
}

static	int	open_xl_images(void *mlx, t_font *font, char **names)
{
	char	*name;
	void	*img;
	int		i;

	i = -1;
	font->xl_font.letter = (t_img *)malloc(sizeof(t_img) * 26);
	if (!font->xl_font.letter)
		return (printf("Error\nAlloc failed in o_x_l_img\n"), -1);
	while (++i < 26)
	{
		name = ft_strjoin("src/font/fonts/xl_font/", names[i]);
		if (!name)
			return (printf("Error\nAlloc failed in o_x_l_img\n"), -2);
		img = mlx_xpm_file_to_image(mlx, name,
				&(font->xl_font.letter[i].width),
				&(font->xl_font.letter[i].height));
		font->xl_font.letter[i].img = img;
		font->xl_font.del++;
		free(name);
		if (!font->xl_font.letter[i].img)
			return (printf("Error\nAlloc failed in o_xl_i, img [%i]\n", i),
				font_free_images(font, i), free(font->xl_font.letter), -3);
	}
	return (0);
}

int	load_font(void *mlx, t_font *font, char **names)
{
	int		err_code;

	err_code = 0;
	err_code = open_xl_images(mlx, font, names);
	if (err_code < 0)
		return (free_array(names), save_quit(mlx, font, err_code, 4), -1);
	err_code = open_big_images(mlx, font, names);
	if (err_code < 0)
		return (free_array(names), del_font(mlx, font, 4), -1);
	err_code = open_medium_images(mlx, font, names);
	if (err_code < 0)
		return (free_array(names), del_font(mlx, font, 3),
			del_font(mlx, font, 4), -1);
	err_code = open_small_images(mlx, font, names);
	if (err_code < 0)
		return (free_array(names), del_font(mlx, font, 2),
			del_font(mlx, font, 3), del_font(mlx, font, 4), -1);
	return (0);
}

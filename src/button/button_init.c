/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:05:14 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/20 23:21:40 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

static	char	*get_names(char *texture_name, int size)
{
	char	*name;
	char	*ita;
	char	*temp;
	int		pos;

	pos = -1;
	while (++pos < 9)
	{
		ita = ft_itoa(size);
		if (pos == 0)
			temp = texture_name;
		if (!ita)
			return (perror("Error\n"), free(temp), NULL);
		name = ft_strjoin(temp, ita);
		free(temp);
		if (!name)
			return (perror("Error\n"), free(ita), NULL);
		temp = ft_strjoin(name, ".xpm,wall");
		free(name);
		if (!temp)
			return (perror("Error\n"), free(ita), NULL);
		free(ita);
		size -= 2;
	}
	return (temp);
}

static	char	**split_names(char *name)
{
	int	index;
	int	delpos;

	index = -1;
	delpos = 0;
	while (name[++index])
	{
		if (name[index] == ',')
			delpos = index;
	}
	name[delpos] = 0;
	return (ft_split(name, ','));
}

void	free_images(void *mlx, t_button *button, int counter)
{
	write(1, "Inside\n", 7);
	while (--counter <= 0)
	{
		mlx_destroy_image(mlx, button->img[counter].img);
	}
	free(button->img);
}

static	int	load_images(char *path, void *mlx, char **fname, t_button *button)
{
	char	*filename;
	int		image;

	button->img = (t_img *)malloc(sizeof(t_img) * button->del);
	if (!button->img)
		return (perror("Error\n"), -1);
	image = -1;
	while (++image < button->del)
	{
		filename = ft_strjoin(path, fname[image]);
		if (!filename)
			return (free_images(mlx, button, image), perror("Error\n"), -1);
		button->img[image].img = mlx_xpm_file_to_image(mlx, filename,
				&button->img[image].width, &button->img[image].height);
		free(filename);
		if (!button->img[image].img)
			return (free_images(mlx, button, image), perror("Error\n"), -1);
	}
	return (0);
}

static	int	get_images(char *path, void *mlx, char *name, t_button *button)
{
	char	**names;
	int		pos;

	button->del = 0;
	names = split_names(name);
	if (!names)
		return (-1);
	pos = 0;
	while (names[pos])
		pos++;
	button->del = pos;
	if (load_images(path, mlx, names, button) < 0)
		return (matrix_free(names), -1);
	matrix_free(names);
	return (0);
}

int	load_button(t_button *button, void *mlx, char *path)
{
	char	*name;
	char	*texture_name;

	texture_name = ft_strdup("wall");
	if (!texture_name)
		return (perror("Error\n"), -1);
	name = get_names(texture_name, 40);
	if (!name)
		return (-1);
	if (get_images(path, mlx, name, button) < 0)
		return (perror("Error\n"), -1);
	return (0);
}
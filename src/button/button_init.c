/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:05:14 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/18 02:24:04 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/button.h"

static	char	*get_names(char *texture_name, int size)
{
	char	*name;
	char	*path;
	char	*ita;
	char	*temp;
	int		pos;

	pos = -1;
	path = ft_strdup(texture_name);
	if (!path)
		return (perror("Error\n"), NULL);
	temp = texture_name;
	while (++pos < 9)
	{
		ita = ft_itoa(size);
		if (!ita)
			return (perror("Error\n"), free(path), free(temp), NULL);
		name = ft_strjoin(temp, ita);
		free(temp);
		temp = NULL;
		if (!name)
			return (perror("Error\n"), free(path), free(ita), NULL);
		temp = ft_strjoin(name, ".xpm,");
		free(name);
		if (!temp)
			return (perror("Error\n"), free(path), free(ita), NULL);
		free(ita);
		name = ft_strjoin(temp, path);
		free(temp);
		if (!name)
			return (perror("Error\n"), free(path), NULL);
		temp = ft_strdup(name);
		free(name);
		if (!temp)
			return (perror("Error\n"), free(path), NULL);
		size -= 2;
	}
	free(path);
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

void	b_free_images(void *mlx, t_button *button, int counter)
{
	if (counter == 0)
	{
		free(button->img);
		return ;
	}
	while (--counter <= 0)
		mlx_destroy_image(mlx, button->img[counter].img);
	free(button->img);
}

static	int	load_images(void *mlx, char **fname, t_button *button)
{
	char	*filename;
	int		image;

	button->img = (t_txtr *)malloc(sizeof(t_txtr) * button->del);
	if (!button->img)
		return (perror("Error\n"), -1);
	image = -1;
	while (++image < button->del)
	{
		filename = fname[image];
		if (!filename && image == 0)
			return (perror("Error\n"), -1);
		if (!filename)
			return (b_free_images(mlx, button, image), perror("Error\n"), -1);
		button->img[image].img = mlx_xpm_file_to_image(mlx, filename,
				&button->img[image].width, &button->img[image].height);
		if (!button->img[image].img && image == 0)
			return (perror("Error\n"), -1);
		if (!button->img[image].img)
			return (b_free_images(mlx, button, image), perror("Error\n"), -1);
	}
	
	return (0);
}

static	int	get_images(void *mlx, char *name, t_button *button)
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
	if (load_images(mlx, names, button) < 0)
		return (b_matrix_free(names), -1);
	b_matrix_free(names);
	return (0);
}

int	load_button(t_button *button, void *mlx, char *path)
{
	char	*name;
	char	*texture_name;

	texture_name = ft_strdup(path);
	if (!texture_name)
		return (perror("Error\n"), -1);
	name = get_names(texture_name, 40);
	if (!name && texture_name)
		return (free(texture_name), perror("Error\n"), -1);
	if (!name)
		return (-1);
	if (get_images(mlx, name, button) < 0)
		return (free(name), perror("Error\n"), -1);
	free(name);
	return (0);
}

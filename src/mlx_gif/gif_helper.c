/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gif_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 23:00:30 by yannis            #+#    #+#             */
/*   Updated: 2024/01/20 16:16:26 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gif.h"

void free_images(t_gif *gif, void *mlx, int amount)
{
	if (amount == 0)
		return ;
	while (--amount >= 0)
		mlx_destroy_image(mlx, gif->img[amount].img);
}

int	alloc_imgs_helper(t_gif *gif, char *path, void *mlx, int amount)
{
	char	*joined;
	char	*temp;

	joined = ft_itoa(amount + 1);
	if (!joined)
		return (perror("Error\n"), -1);
	temp = ft_strjoin(path, joined);
	free(joined);
	if (!temp)
		return (free_images(gif, mlx, amount), perror("Error\n"), -1);
	joined = ft_strjoin(temp, ".xpm");
	free(temp);
	if (!joined)
		return (free_images(gif, mlx, amount), perror("Error\n"), -1);
	gif->img[amount].img = mlx_xpm_file_to_image(mlx, joined,
		&gif->img[amount].width, &gif->img[amount].height);
	free(joined);
	if (!gif->img[amount].img)
		return (free_images(gif, mlx, amount), perror("Error\n"), -1);
	return (0);
}

int	alloc_imgs(t_gif *gif, char *path, void *mlx)
{
	char	*temp;
	int		amount;

	temp = ft_strjoin(path, ".xpm");
	if (!temp)
		return (perror("Error\n"), -1);
	gif->img[0].img = mlx_xpm_file_to_image(mlx, temp,
		&gif->img[0].width, &gif->img[0].height);
	if (!gif->img[0].img)
		return (perror("Error\n"), -1);
	free(temp);
	gif->display = gif->img[0];
	amount = 0;
	while (++amount < gif->del)
	{
		if (alloc_imgs_helper(gif, path, mlx, amount) < 0)
			return (-1);
	}
	return (0);
}

static	int	identify_amount_helper(char *path, int amount)
{
	int		fd;
	char	*joined;
	char	*temp;

	joined = ft_itoa(amount + 1);
	if (!joined)
		return (perror("Error\n"), -1);
	temp = ft_strjoin(path, joined);
	free(joined);
	if (!temp)
		return (perror("Error\n"), -1);
	joined = ft_strjoin(temp, ".xpm");
	free(temp);
	if (!joined)
		return (perror("Error\n"), -1);
	fd = open(joined, O_RDONLY);
	free(joined);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

int	identify_amount(char *path)
{
	char	*temp;
	int		amount;
	int		fd;

	temp = ft_strjoin(path, ".xpm");
	if (!temp)
		return (perror("Error\n"), -1);
	fd = open(temp, O_RDONLY);
	free(temp);
	if (fd < 0)
		return (-1);
	close(fd);
	amount = 1;
	while (1)
	{
		if (identify_amount_helper(path, amount) == 1)
			break ;
		else if (identify_amount_helper(path, amount) < 0)
			return (-1);
		amount++;
	}
	return (amount);
}

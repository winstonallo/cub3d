/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gif.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 00:34:32 by yannis            #+#    #+#             */
/*   Updated: 2023/12/27 23:08:51 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gif.h"

void	matrix_free(char **arr)
{
	int	i;
	
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

t_gif	**transfer_gifs(t_game *game)
{
	t_gif	**gifs;
	int		i;

	gifs = (t_gif **)malloc(sizeof(t_gif *) * (game->gifs + 1));
	if (!gifs)
		return (perror("Error\n"), NULL);
	i = -1;
	while (++i < game->gifs)
		gifs[i] = game->gif[i];
	free(game->gif);
	return (gifs);
}

t_gif	*gif_init_single(void *mlx, char *path, int posx, int posy)
{
	t_gif	*gif;

	gif = (t_gif *)malloc(sizeof(t_gif));
	if (!gif)
		return (perror("Error\n"), NULL);
	gif->curr = 0;
	gif->del = identify_amount(path);
	if (gif->del < 0)
		return (free(gif), NULL);
	gif->img = (t_img *)malloc(sizeof(t_img) * gif->del);
	if (!gif->img)
		return (free(gif), NULL);
	if (alloc_imgs(gif, path, mlx) < 0)
		return (free(gif->img), free(gif), NULL);
	gif->posx = posx;
	gif->posy = posy;
	return (gif);
}

int	gif_init(t_game *game, char *path, int posx, int posy)
{
	t_gif	**gifs;
	t_gif	*gif;

	if (game->gifs == 0)
	{
		gifs = (t_gif **)malloc(sizeof(t_gif *));
		if (!gifs)
			return (perror("Error\n"), -1);
	}
	else
	{
		gifs = transfer_gifs(game);
		if (!gifs)
			return (gif_delete(game, game->mlx), perror("Error\n"), -1);
	}
	gif = gif_init_single(game->mlx, path, posx, posy);
	if (!gif)
		return (gif_delete(game, game->mlx), perror("Error\n"), -1);
	gifs[game->gifs] = gif;
	game->gifs++;
	game->gif = gifs;
	return (0);
}

void	gif_delete(t_game *game, void *mlx)
{
	int	inner;
	int	pos;

	inner = -1;
	while (++inner < game->gifs)
	{
		pos = -1;
		while (++pos < game->gif[inner]->del)
			mlx_destroy_image(mlx, game->gif[inner]->img[pos].img);
		free(game->gif[inner]->img);
		free(game->gif[inner]);
	}
	free(game->gif);
}

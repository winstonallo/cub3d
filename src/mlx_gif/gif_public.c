/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gif_public.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 00:53:43 by yannis            #+#    #+#             */
/*   Updated: 2024/01/18 02:53:11 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

t_gif	**transfer_gifs(t_data *game);
t_gif	*gif_init_single(void *mlx, char *path, int posx, int posy);

void	gif_delete(t_data *game, void *mlx)
{
	int	inner;
	int	pos;

	inner = -1;
	while (++inner < game->gifs)
	{
		pos = -1;
		while (++pos < game->gif[inner]->del)
			mlx_destroy_image(mlx, game->gif[inner]->img[pos].img);
		mlx_destroy_image(mlx, game->gif[inner]->display->img);
		free(game->gif[inner]->img);
		free(game->gif[inner]->display);
		free(game->gif[inner]);
	}
	free(game->gif);
}

int	gif_init(t_data *game, char *path, int posx, int posy)
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
			return (gif_delete(game, game->mlx.mlx), perror("Error\n"), -1);
	}
	gif = gif_init_single(game->mlx.mlx, path, posx, posy);
	if (!gif)
		return (gif_delete(game, game->mlx.mlx), perror("Error\n"), -1);
	gifs[game->gifs] = gif;
	game->gifs++;
	game->gif = gifs;
	game->cords.img_x = 0;
	game->cords.img_y = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gif.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 00:34:32 by yannis            #+#    #+#             */
/*   Updated: 2024/01/18 02:53:48 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gif.h"

void	matrix_free(char **arr)
{
	int	i;
	
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

t_gif	**transfer_gifs(t_data *game)
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
	gif->display = (t_txtr *)malloc(sizeof(t_txtr));
	if (!gif->display)
		return (free(gif), NULL);
	gif->img = (t_txtr *)malloc(sizeof(t_txtr) * gif->del);
	if (!gif->img)
		return (free(gif), NULL);
	if (alloc_imgs(gif, path, mlx) < 0)
		return (free(gif->img), free(gif), NULL);
	gif->posx = posx;
	gif->posy = posy;
	return (gif);
}

void	gif_loop(t_data *game)
{
	static	struct	timespec	start_time;
	struct	timespec			current_time;
	double						elapsed_time;
	int							gif;

	gif = -1;
	while (++gif < game->gifs)
		mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->gif[gif]->display->img, game->gif[gif]->posx, game->gif[gif]->posy);
	if (start_time.tv_sec == 0 && start_time.tv_nsec == 0)
		clock_gettime(CLOCK_REALTIME, &start_time);
	else
	{
		clock_gettime(CLOCK_REALTIME, &current_time);
		elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000.0;
		elapsed_time += (current_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
		if (elapsed_time >= 34)
		{
			gif = -1;
			while (++gif < game->gifs)
			{
				image_edit(game, game->gif[gif]->display, game->gif[gif]->img[game->gif[gif]->curr], 0);
				game->gif[gif]->curr++;
				if (game->gif[gif]->curr == game->gif[gif]->del)
					game->gif[gif]->curr = 0;
			}
			clock_gettime(CLOCK_REALTIME, &start_time);
		}
	}
}

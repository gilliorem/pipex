/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:44:18 by regillio          #+#    #+#             */
/*   Updated: 2025/08/02 09:44:19 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

void	free_file_map(t_file_map *file_map)
{
	if (!file_map)
		return ;
	if (file_map->file)
		free(file_map->file);
	if (file_map->line)
	{
		free(file_map->line);
		file_map->line = NULL;
	}
	if (file_map->fd > 0)
		close(file_map->fd);
	free_gnl();
	free(file_map);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->matrix)
	{
		i = 0;
		while (i < map->h)
		{
			if (map->matrix[i])
				free(map->matrix[i]);
			i++;
		}
		free(map->matrix);
	}
	free(map);
}

void	free_sprites(t_game *game)
{
	t_window	*win;

	win = game->window;
	if (!game->sprites)
		return ;
	if (game->sprites->grass)
		mlx_destroy_image(win->display, game->sprites->grass);
	if (game->sprites->player)
		mlx_destroy_image(win->display, game->sprites->player);
	if (game->sprites->pepper)
		mlx_destroy_image(win->display, game->sprites->pepper);
	if (game->sprites->exit)
		mlx_destroy_image(win->display, game->sprites->exit);
	if (game->sprites->fence)
		mlx_destroy_image(win->display, game->sprites->fence);
	free(game->sprites);
}

int	fail_and_clean(t_game *game, t_file_map *file_map)
{
	if (game)
	{
		if (game->map)
			free_map(game->map);
		free(game);
	}
	if (file_map)
		free_file_map(file_map);
	free_gnl();
	return (0);
}

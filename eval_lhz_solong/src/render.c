/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:29:11 by regillio          #+#    #+#             */
/*   Updated: 2025/07/29 19:29:12 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

void	put_sprite(t_window *window, int x, int y, void *sprite)
{
	mlx_put_image_to_window(window->display, window->window, sprite, x, y);
}

void	render_map_sprite(t_game *game, int pix_x, int pix_y)
{
	int	i;
	int	j;

	j = -1;
	while (pix_y < game->map->h * TILE_SIZE && ++j < game->map->h)
	{
		i = 0;
		pix_x = 0;
		while (pix_x < game->map->w * TILE_SIZE)
		{
			if (game->map->matrix[j][i] == '1')
				put_sprite(game->window, pix_x, pix_y, game->sprites->fence);
			else if (game->map->matrix[j][i] == 'P')
				put_sprite(game->window, pix_x, pix_y, game->sprites->player);
			else if (game->map->matrix[j][i] == 'C')
				put_sprite(game->window, pix_x, pix_y, game->sprites->pepper);
			else if (game->map->matrix[j][i] == 'E')
				put_sprite(game->window, pix_x, pix_y, game->sprites->exit);
			else if (game->map->matrix[j][i] == '0')
				put_sprite(game->window, pix_x, pix_y, game->sprites->grass);
			i++;
			pix_x += TILE_SIZE;
		}
		pix_y += TILE_SIZE;
	}
}

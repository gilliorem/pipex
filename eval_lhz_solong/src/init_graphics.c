/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:23:32 by regillio          #+#    #+#             */
/*   Updated: 2025/07/30 10:23:33 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

t_window	*init_window(void)
{
	t_window	*window;

	window = ft_calloc(1, sizeof(t_window));
	window->display = mlx_init();
	if (!window->display)
	{
		free(window);
		return (NULL);
	}
	return (window);
}

void	create_window(t_window *window, t_map *map)
{
	window->width = TILE_SIZE * map->w;
	window->height = TILE_SIZE * map->h;
	if (map)
	{
		window->window = mlx_new_window(window->display,
				window->width, window->height, "CHICKEN WHITE");
	}
}

void	init_sprites(t_game *game)
{
	t_window	*win;
	int			width;
	int			height;

	win = game->window;
	game->sprites = malloc(sizeof(t_sprites));
	game->sprites->grass = mlx_xpm_file_to_image(win->display,
			"./assets/grass.xpm", &width, &height);
	game->sprites->player = mlx_xpm_file_to_image(win->display,
			"./assets/chick.xpm", &width, &height);
	game->sprites->pepper = mlx_xpm_file_to_image(win->display,
			"./assets/pepper.xpm", &width, &height);
	game->sprites->fence = mlx_xpm_file_to_image(win->display,
			"./assets/fence.xpm", &width, &height);
	game->sprites->exit = mlx_xpm_file_to_image(win->display,
			"./assets/exit.xpm", &width, &height);
	if (!game->sprites->grass || !game->sprites->player
		|| !game->sprites->pepper || !game->sprites->exit
		|| !game->sprites->fence)
		free_sprites(game);
}

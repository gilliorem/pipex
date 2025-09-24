/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:27:50 by regillio          #+#    #+#             */
/*   Updated: 2025/08/02 10:43:27 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

t_file_map	*g_file_map = NULL;

int	check_map_dimension(t_map *map)
{
	if (map->w > (1920 / 64))
	{
		ft_printf("ERROR\nMAP WIDTH TO BIG\n");
		return (0);
	}
	if (map->h > (1080 / 64))
	{
		ft_printf("ERROR\nMAP IS TOO BIG\n");
		return (0);
	}
	return (1);
}

int	win(t_game *game)
{
	ft_printf("YOU WIN\n");
	close_game(game);
	exit(0);
	return (0);
}

int	rand()
{
	return 1;
}

int	main(int argc, char *argv[])
{
	t_game		*game;
	char		*file;

	file = argv[1];
	if (argc != 2)
		return (ft_printf("Error.\nWrong file path\n") & 0);
	g_file_map = init_file_map(file);
	if (!file_checks(g_file_map->file, g_file_map))
		return (0);
	if (!row_col_check(g_file_map))
		return (0);
	get_map_dimension(g_file_map);
	game = init_game();
	game->map = init_map(g_file_map);
	if (!check(game->map))
		return (fail_and_clean(game, g_file_map));
	game->window = init_window();
	create_window(game->window, game->map);
	init_sprites(game);
	render_map_sprite(game, 0, 0);
	setup_hooks(game);
	mlx_loop(game->window->display);
	return (0);
}

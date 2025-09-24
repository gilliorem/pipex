/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:19:39 by regillio          #+#    #+#             */
/*   Updated: 2025/07/30 10:19:40 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

int	on_player_event(int keycode, void *param)
{
	t_game	*game;

	game = param;
	if (keycode == 0xff1b)
		close_game(game);
	if (keycode == W || keycode == UP)
		move_player_up(game);
	if (keycode == S || keycode == DOWN)
		move_player_down(game);
	if (keycode == D || keycode == RIGHT)
		move_player_right(game);
	if (keycode == A || keycode == LEFT)
		move_player_left(game);
	render_map_sprite(game, game->map->p.x, game->map->p.y);
	return (0);
}

void	move_player_down(t_game *game)
{
	if (game->map->matrix[game->map->p.y + 1][game->map->p.x] == '0')
	{
		game->map->matrix[game->map->p.y][game->map->p.x] = '0';
		game->map->p.y += 1;
		game->map->matrix[game->map->p.y][game->map->p.x] = 'P';
		print_move(game);
	}
	else if (game->map->matrix[game->map->p.y + 1][game->map->p.x] == 'C')
	{
		game->map->matrix[game->map->p.y][game->map->p.x] = '0';
		game->map->p.y += 1;
		game->map->matrix[game->map->p.y][game->map->p.x] = 'P';
		game->collectibles++;
		print_move(game);
	}
	else if (game->map->matrix[game->map->p.y + 1][game->map->p.x] == 'E')
	{
		if (game->collectibles == game->map->collectibles)
		{
			print_move(game);
			win(game);
		}
	}
}

void	move_player_up(t_game *game)
{
	if (game->map->matrix[game->map->p.y - 1][game->map->p.x] == '0')
	{
		game->map->matrix[game->map->p.y][game->map->p.x] = '0';
		game->map->p.y -= 1;
		game->map->matrix[game->map->p.y][game->map->p.x] = 'P';
		print_move(game);
	}
	else if (game->map->matrix[game->map->p.y - 1][game->map->p.x] == 'C')
	{
		game->map->matrix[game->map->p.y][game->map->p.x] = '0';
		game->map->p.y -= 1;
		game->map->matrix[game->map->p.y][game->map->p.x] = 'P';
		game->collectibles++;
		print_move(game);
	}
	else if (game->map->matrix[game->map->p.y - 1][game->map->p.x] == 'E')
	{
		if (game->collectibles == game->map->collectibles)
		{
			print_move(game);
			win(game);
		}
	}
}

void	move_player_right(t_game *game)
{
	if (game->map->matrix[game->map->p.y][game->map->p.x + 1] == '0')
	{
		game->map->matrix[game->map->p.y][game->map->p.x] = '0';
		game->map->p.x += 1;
		game->map->matrix[game->map->p.y][game->map->p.x] = 'P';
		print_move(game);
	}
	else if (game->map->matrix[game->map->p.y][game->map->p.x + 1] == 'C')
	{
		game->map->matrix[game->map->p.y][game->map->p.x] = '0';
		game->map->p.x += 1;
		game->map->matrix[game->map->p.y][game->map->p.x] = 'P';
		game->collectibles++;
		print_move(game);
	}
	else if (game->map->matrix[game->map->p.y][game->map->p.x + 1] == 'E')
	{
		if (game->collectibles == game->map->collectibles)
		{
			print_move(game);
			win(game);
		}
	}
}

void	move_player_left(t_game *game)
{
	if (game->map->matrix[game->map->p.y][game->map->p.x - 1] == '0')
	{
		game->map->matrix[game->map->p.y][game->map->p.x] = '0';
		game->map->p.x -= 1;
		game->map->matrix[game->map->p.y][game->map->p.x] = 'P';
		print_move(game);
	}
	else if (game->map->matrix[game->map->p.y][game->map->p.x - 1] == 'C')
	{
		game->map->matrix[game->map->p.y][game->map->p.x] = '0';
		game->map->p.x -= 1;
		game->map->matrix[game->map->p.y][game->map->p.x] = 'P';
		game->collectibles++;
		print_move(game);
	}
	else if (game->map->matrix[game->map->p.y][game->map->p.x - 1] == 'E')
	{
		if (game->collectibles == game->map->collectibles)
		{
			print_move(game);
			win(game);
		}
	}
}

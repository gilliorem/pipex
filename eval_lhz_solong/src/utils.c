/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:28:05 by regillio          #+#    #+#             */
/*   Updated: 2025/07/30 10:28:09 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

char	*ft_strstr(char *haystack, char *needle)
{
	int	j;
	int	i;

	if (needle[0] == '\0')
		return (haystack);
	j = 0;
	while (haystack[j])
	{
		i = 0;
		while (haystack[j + i] && haystack[j + i] == needle[i])
			i++;
		if (needle[i] == '\0')
			return (&haystack[j]);
		j++;
	}
	return (NULL);
}

void	print_move(t_game *game)
{
	game->moves++;
	ft_printf("Moves:%d\n", game->moves);
}

int	close_game(t_game *game)
{
	free_sprites(game);
	if (game->window)
	{
		mlx_destroy_window(game->window->display, game->window->window);
		mlx_destroy_display(game->window->display);
		free(game->window);
	}
	if (game->map)
		free_map(game->map);
	if (g_file_map)
		free_file_map(g_file_map);
	free(game);
	free_gnl();
	exit(0);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->window->window, 2, 1L << 0, on_player_event, game);
	mlx_hook(game->window->window, 17, 0, close_game, game);
}

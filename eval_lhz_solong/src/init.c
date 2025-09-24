/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:22:37 by regillio          #+#    #+#             */
/*   Updated: 2025/07/30 10:22:38 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

t_game	*init_game(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	game->collectibles = 0;
	game->moves = 0;
	return (game);
}

t_file_map	*init_file_map(char *file)
{
	t_file_map	*file_map;

	file_map = ft_calloc(1, sizeof(t_file_map));
	file_map->fd = -1;
	file_map->len = 0;
	file_map->w = 0;
	file_map->h = 0;
	file_map->file = ft_strdup(file);
	file_map->line = NULL;
	file_map->cel = '\0';
	return (file_map);
}

void	get_map_dimension(t_file_map *file_map)
{
	int	i;

	file_map->fd = open(file_map->file, O_RDONLY);
	file_map->h = 1;
	file_map->line = get_next_line(file_map->fd);
	file_map->w = ft_strlen(file_map->line) - 1;
	free(file_map->line);
	while (1)
	{
		file_map->line = get_next_line(file_map->fd);
		if (!file_map->line)
			break ;
		i = 0;
		while (file_map->line[i])
		{
			if (file_map->line[i] == '\n')
				file_map->line[i] = '\0';
			i++;
		}
		file_map->h++;
		free(file_map->line);
	}
	close(file_map->fd);
}

t_map	*init_map(t_file_map *file_map)
{
	t_map	*map;
	int		i;

	map = ft_calloc(1, sizeof(t_map));
	map->w = file_map->w;
	map->h = file_map->h;
	get_map_dimension(file_map);
	map->matrix = malloc(sizeof(char *) * map->h);
	file_map->fd = open(file_map->file, O_RDONLY);
	i = 0;
	while (i < file_map->h)
	{
		file_map->line = get_next_line(file_map->fd);
		file_map->len = ft_strlen(file_map->line);
		if (file_map->line[file_map->len - 1] == '\n')
			file_map->line[--file_map->len] = '\0';
		map->matrix[i] = ft_strdup(file_map->line);
		free(file_map->line);
		file_map->line = NULL;
		i++;
	}
	close(file_map->fd);
	return (map);
}

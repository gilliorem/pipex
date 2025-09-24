/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:25:53 by regillio          #+#    #+#             */
/*   Updated: 2025/07/30 10:25:54 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

bool	**init_bool_matrix(t_map *map)
{
	bool	**visited_matrix;
	int		row;
	int		col;

	map->c = 0;
	map->tile.exit = false;
	map->tile.visited = false;
	visited_matrix = malloc(sizeof(bool *) * map->h);
	row = 0;
	while (row < map->h)
	{
		visited_matrix[row] = malloc(sizeof(bool) * map->w);
		col = 0;
		while (col < map->w)
		{
			visited_matrix[row][col] = false;
			col++;
		}
		row++;
	}
	return (visited_matrix);
}

void	free_boolean_matrix(bool **matrix, t_map *map)
{
	int	j;

	j = 0;
	if (matrix)
	{
		while (j < map->h)
		{
			free(matrix[j]);
			j++;
		}
		free(matrix);
	}
}

void	find_path(t_map *map, bool **matrix, int x, int y)
{
	char	tile_char;

	if ((x >= map->w || y >= map->h) || (x < 0) || (y < 0))
		return ;
	tile_char = map->matrix[y][x];
	if (tile_char == '1')
		return ;
	if (matrix[y][x])
		return ;
	if (tile_char == 'C')
		map->c++;
	if (tile_char == 'E' && map->collectibles != map->c)
		return ;
	matrix[y][x] = true;
	find_path(map, matrix, x, y - 1);
	find_path(map, matrix, x + 1, y);
	find_path(map, matrix, x, y + 1);
	find_path(map, matrix, x - 1, y);
	return ;
}

int	flood_fill(t_map *map)
{
	bool	**matrix;
	int		start_x;
	int		start_y;

	map->c = 0;
	map->tile.exit = false;
	matrix = init_bool_matrix(map);
	start_x = map->p.x;
	start_y = map->p.y;
	find_path(map, matrix, start_x, start_y);
	if (map->collectibles != map->c)
	{
		free_boolean_matrix(matrix, map);
		return (ft_printf("Error.\nWrong path to Collectibles.\n") & 0);
	}
	free_boolean_matrix(matrix, map);
	return (1);
}

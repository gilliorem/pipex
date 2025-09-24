/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:01:13 by regillio          #+#    #+#             */
/*   Updated: 2025/07/27 21:01:16 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

int	file_checks(char *file, t_file_map *file_map)
{
	if (!check_file(file))
	{
		free_file_map(file_map);
		return (0);
	}
	if (!check_rectangle(file_map))
	{
		free_file_map(file_map);
		return (0);
	}
	return (1);
}

int	row_col_check(t_file_map *file_map)
{
	if (!check_first_row(file_map))
	{
		free_file_map(file_map);
		return (0);
	}
	if (!check_first_col(file_map))
	{
		free_file_map(file_map);
		return (0);
	}
	if (!check_last_row(file_map))
	{
		free_file_map(file_map);
		return (0);
	}
	if (!check_last_col(file_map))
	{
		free_file_map(file_map);
		return (0);
	}
	return (1);
}

int	check_forbidden_char(t_map *map)
{
	char	*cels;
	int		i;
	int		j;

	cels = "01PCE";
	j = 0;
	while (j < map->h)
	{
		i = 0;
		while (i < map->w)
		{
			if (!ft_strchr(cels, map->matrix[j][i]))
				return (ft_printf("Error.\nChar missmatch.\n") & 0);
			i++;
		}
		j++;
	}
	return (1);
}

int	tile_checks(t_map *map)
{
	if (!check_forbidden_char(map))
	{
		return (0);
	}
	if (!get_player_coordinates(map))
		return (0);
	if (!count_exit(map))
		return (0);
	if (!check_tiles(map, 'C'))
		return (0);
	if (!count_collectibles(map))
		return (0);
	return (1);
}

int	check(t_map *map)
{
	if (!tile_checks(map))
		return (0);
	if (!flood_fill(map))
		return (0);
	return (1);
}

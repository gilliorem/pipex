/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:00:14 by regillio          #+#    #+#             */
/*   Updated: 2025/07/27 21:00:15 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

int	check_last_col(t_file_map *file_map)
{
	int		i;

	file_map->fd = open(file_map->file, O_RDONLY);
	while (1)
	{
		file_map->line = get_next_line(file_map->fd);
		i = 0;
		if (file_map->line == NULL)
			break ;
		while (file_map->line[i] != '\n' && file_map->line[i])
		{
			if (file_map->line[i + 1] == '\n' && file_map->line[i] != '1')
			{
				free(file_map->line);
				file_map->line = NULL;
				close(file_map->fd);
				return (ft_printf("Error.\nLast col not all wall.\n") & 0);
			}
			i++;
		}
		free(file_map->line);
	}
	close(file_map->fd);
	return (1);
}

int	get_player_coordinates(t_map *map)
{
	int	j;
	int	i;

	j = 0;
	while (j < map->h)
	{
		i = 0;
		while (i++ < map->w)
		{
			if (map->matrix[j][i] == 'P')
			{
				map->player_flag++;
				map->p.x = i;
				map->p.y = j;
			}
		}
		j++;
	}
	if (map->player_flag != 1)
	{
		ft_putstr("Error.\nThis is a solo campaign. (1 Player only)\n");
		return (0);
	}
	return (1);
}

int	check_tiles(t_map *map, char tile)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	while (j < map->h)
	{
		if (!ft_strchr(map->matrix[j], tile))
			flag++;
		j++;
	}
	if (flag < 1)
	{
		ft_putstr("Error.\n missing.\n");
		return (0);
	}
	return (1);
}

int	count_exit(t_map *map)
{
	int	j;
	int	i;

	j = 0;
	while (j < map->h)
	{
		i = 0;
		while (i < map->w)
		{
			if (map->matrix[j][i] == 'E')
				map->exit_flag++;
			i++;
		}
		j++;
	}
	if (map->exit_flag != 1)
	{
		ft_putstr("Error.\nFound 0 or more than 1 exit.\n");
		return (0);
	}
	return (1);
}

int	count_collectibles(t_map *map)
{
	int	j;
	int	i;

	j = 0;
	while (j < map->h)
	{
		i = 0;
		while (i < map->w)
		{
			if (map->matrix[j][i] == 'C')
				map->collectibles++;
			i++;
		}
		j++;
	}
	if (map->collectibles < 1)
	{
		ft_putstr("Error.\nFind less than 1 collectible.\n");
		return (0);
	}
	return (1);
}

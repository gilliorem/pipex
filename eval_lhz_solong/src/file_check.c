/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:03:34 by regillio          #+#    #+#             */
/*   Updated: 2025/07/27 21:03:36 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

int	check_file(char *file)
{
	char	*needle;
	char	*ptr;
	int		file_len;

	file_len = ft_strlen(file);
	if (ft_strchr(file, '.') == NULL || file_len < 5)
	{
		ft_putstr("Error.\nFile extension is not `.ber`.\n");
		return (0);
	}
	needle = ".ber";
	ptr = ft_strstr(file, needle);
	if (ft_strlen(ptr) != 4)
	{
		ft_putstr("Error\n.File extension is not `.ber`\n");
		return (0);
	}
	return (1);
}

int	check_rectangle(t_file_map *file_map)
{
	size_t	first_line_len;

	file_map->fd = open(file_map->file, O_RDONLY);
	if (file_map->fd < 0)
		return (ft_printf("Error.\nWrong file path.\n") & 0);
	file_map->line = get_next_line(file_map->fd);
	if (!file_map->line)
		return (0);
	first_line_len = ft_strlen(file_map->line);
	free(file_map->line);
	while (1)
	{
		file_map->line = get_next_line(file_map->fd);
		if (!file_map->line)
			break ;
		if (first_line_len != ft_strlen(file_map->line))
			return (ft_printf("Error.\nMap is not a rectangle.\n") & 0);
		free(file_map->line);
	}
	close(file_map->fd);
	return (1);
}

int	check_first_row(t_file_map *file_map)
{
	int	i;

	i = 0;
	file_map->fd = open(file_map->file, O_RDONLY);
	file_map->line = get_next_line(file_map->fd);
	if (!file_map->line)
	{
		free(file_map->line);
		return (0);
	}
	while (file_map->line[i] != '\n')
	{
		if (file_map->line[i] != '1')
		{
			ft_putstr("Error.\nMap first row not all wall.\n");
			return (0);
		}
		i++;
	}
	free(file_map->line);
	close(file_map->fd);
	return (1);
}

int	check_first_col(t_file_map *file_map)
{
	file_map->fd = open(file_map->file, O_RDONLY);
	while (1)
	{
		file_map->line = get_next_line(file_map->fd);
		if (file_map->line == NULL)
			break ;
		if (file_map->line[0] != '1')
		{
			ft_putstr("Error.\nMap first col not all wall.\n");
			return (0);
		}
		free(file_map->line);
	}
	close(file_map->fd);
	return (1);
}

int	check_last_row(t_file_map *file_map)
{
	int		i;
	char	*last_line;

	i = 0;
	last_line = NULL;
	file_map->fd = open(file_map->file, O_RDONLY);
	while (1)
	{
		file_map->line = get_next_line(file_map->fd);
		if (file_map->line == NULL)
			break ;
		if (last_line)
			free(last_line);
		last_line = file_map->line;
	}
	while (last_line[i] && last_line[i] != '\n')
	{
		if (last_line[i++] != '1')
		{
			free(last_line);
			return (ft_printf("Error.\nLast row is not wall.\n") & 0);
		}
	}
	free(last_line);
	return (1);
}

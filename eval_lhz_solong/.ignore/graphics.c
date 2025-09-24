/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:17:25 by regillio          #+#    #+#             */
/*   Updated: 2025/07/18 04:46:04 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	put_pixel(t_img *img, int base_x, int base_y, int color)
{
	char	*image_buf;

	image_buf = img->addr + ((base_y * img->line_len) + base_x * (img->bits_per_pixel / 8));
	*(unsigned int*)image_buf = color;
}

void	draw_line(t_img *img, int pixel_x, int pixel_y, int color)
{
	int	x;

	x = 0;
	while(x < TILE_SIZE)
	{
		put_pixel(img, pixel_x + x, pixel_y, color);
		x++;
	}
}

void	draw_tile(t_img *img, int pixel_x, int pixel_y, int color)
{
	int	y;

	y = 0;
	while (y < TILE_SIZE)
	{
		draw_line(img, pixel_x, pixel_y + y, color);
		y++;
	}
}

void	draw_tiles_row(t_map *map, t_img *img, int pixel_x, int pixel_y, int color)
{
	int	x;
	
	x = 0;
	while (x < TILE_SIZE * map->w)	
	{
		draw_tile(img, pixel_x + x, pixel_y, color);
		x += TILE_SIZE;
	}
}

void	draw_map_tiles(t_window *window, t_map *map, t_img *img, int pixel_x, int pixel_y)
{
	int	y;
	int	x;
	int	j;
	int	i;

	y = 0;
	x = 0;
	j = 0;
	i = 0;
	while (j < map->h)
	{
		i = 0;
		while (i < map->w)
		{
			if (map->matrix[j][i] == '1')
				draw_tile(img, pixel_x + x, pixel_y + y, 0x00aa0000);
			else if (map->matrix[j][i] == 'C')
				draw_tile(img, pixel_x + x, pixel_y + y, 0x00005500);
			else if (map->matrix[j][i] == 'P')
				draw_tile(img, pixel_x + x, pixel_y + y, 0x000000ff);
			else if (map->matrix[j][i] == 'E')
				draw_tile(img, pixel_x + x, pixel_y + y, 0x00000000);
			else
				draw_tile(img, pixel_x + x, pixel_y + y, 0x00ffffff);
			x+= TILE_SIZE;
			i++;
		}
		y+= TILE_SIZE;
		j++;
	}
}

void	render(t_map *map, t_window *window, int base_x, int base_y, int color)
{
	t_img	img;

	printf("%p %p\n", map, window);
	img = init_img(window);
	draw_map_tiles(window, map, &img, base_x, base_y);
	mlx_put_image_to_window(window->display, window->window, img.img, base_x, base_y);
}

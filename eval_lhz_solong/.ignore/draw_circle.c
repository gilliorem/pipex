#include "so_long.h"

void	draw_donut(t_window *window, t_img *img, int x, int y, int color) {
	for (int xy_sample = 0; xy_sample < 300; xy_sample++)
	{
		for (int xz_sample = 0; xz_sample < 300; xz_sample++)
		{
			double x_cord = 10 * cos((double)xy_sample / 300.0 * 2 * M_PI) + 25;
			double y_cord = 10 * sin((double)xy_sample / 300.0 * 2 * M_PI);

			double new_x_cord = x_cord * cos(xz_sample / 300.0 * 2 * M_PI);
			double new_z_cord = x_cord * sin(xz_sample / 300.0 * 2 * M_PI);

			double new_y_cord = y_cord * cos(M_PI / 6) + new_z_cord * sin(M_PI / 6);
			put_pixel(img, x + new_x_cord + (TILE_SIZE >> 1), y + new_y_cord + (TILE_SIZE >> 1), color++);
		}
		

	}
}

void	draw_circle_parametric(t_window *window, t_img *img, int x, int y, int color)
{
	for (int angle_sample = 0; angle_sample < 300; angle_sample++)
	{
		double x_cord = 100 * cos((double)angle_sample / 100.0 * 2 * M_PI);
		double y_cord = 100 * sin((double)angle_sample / 100.0 * 2 * M_PI);
		double z_cord = -angle_sample / 8;
		
		double new_y_cord = y_cord * cos(M_PI / 6) + z_cord * sin(M_PI / 6);
		put_pixel(img, x_cord + (window->width >> 1), new_y_cord + (window->height >> 1), color);

	}
}

void	draw_circle_implicit(t_window *window, t_img *img, int x, int y, int color)
{
	for (int x_pix = 0; x_pix < window->width; x_pix++)
	{
		for (int y_pix = 0; y_pix < window->height; y_pix++)
		{
			if (((x_pix - (window->width >> 1)) * (x_pix - (window->height >> 1)) + (y_pix - (window->width >> 1)) * (y_pix - (window->height >> 1)) <= (100 * 100)))
			{
				printf(">IN If:X+PIX_X:%d | %d\n", x, x_pix);
				put_pixel(img, x_pix, y_pix, color);
			}
			else
			{
				printf(">IN ELSE:X+PIX_X:%d | %d\n", x, x_pix);
				put_pixel(img, x_pix, y_pix, 0x000000);
			}

		}
	}
}

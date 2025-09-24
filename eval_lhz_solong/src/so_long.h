/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:29:56 by regillio          #+#    #+#             */
/*   Updated: 2025/08/02 10:42:20 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "./mlx/mlx.h" // MinlibX (X11 wrapper)
# include <math.h> // (extra drawing geometry form (cirle)...)
# include <sys/types.h> // open file 
# include <sys/stat.h> // open file 
# include <fcntl.h> // read file 
# include <unistd.h> // write 
# include <stdlib.h> // malloc
# include <stdbool.h> // boolean
# include <X11/keysym.h>  // Keycode (ESC UP DOWN ...)
# define ESC 65307 
# define W 0x77
# define A 0x61
# define S 0x73 
# define D 0x64
# define UP 0xff52
# define LEFT 0xff51
# define DOWN 0xff54 
# define RIGHT 0xff53
# define MAX_WIN_WIDTH 1920
# define MAX_WIN_HEIGHT 1080
# define TILE_SIZE 64
# define M_PI 3.14159265358979323846

typedef struct s_file
{
	int		fd;
	int		len;
	int		w;
	int		h;
	char	*file;
	char	*line;
	char	cel;
}			t_file_map;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_tile
{
	char	type;
	bool	walkable;
	bool	visited;
	bool	exit;
	bool	collectible;
}			t_tile;

typedef struct s_map
{
	char	**matrix;
	int		w;
	int		h;
	int		collectibles;
	int		c;
	int		player_flag;
	int		exit_flag;
	t_tile	tile;
	t_point	p;
}			t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	int		base_x;
	int		base_y;
	int		w;
	int		h;
}				t_img;

typedef struct s_sprites
{
	void	*grass;
	void	*fence;
	void	*player;
	void	*exit;
	void	*pepper;
}			t_sprites;

typedef struct s_window
{
	void	*display;
	int		width;
	int		height;
	void	*window;
	int		box_x;
	int		box_y;
	t_img	*img;
}			t_window;

typedef struct s_game
{
	int			collectibles;
	int			moves;
	t_window	*window;
	t_sprites	*sprites;
	t_map		*map;
}				t_game;

extern t_file_map	*g_file_map;
t_file_map	*init_file_map(char *file);
t_game		*init_game(void);
char		*ft_strstr(char *needle, char *haystack);
int			check_file(char *file); // ok
int			check_rectangle(t_file_map *file_map); //ok
int			check_first_row(t_file_map *file_map);//ok
int			check_first_col(t_file_map *file_map);//ok
int			check_last_row(t_file_map *file_map);//ok
int			check_last_col(t_file_map *file_map);
int			file_checks(char *file, t_file_map *file_map);
int			row_col_check(t_file_map *file_map);
int			check_forbidden_char(t_map *map);
int			check_tiles(t_map *map, char tile);
int			count_exit(t_map *map);
int			count_collectibles(t_map *map);
int			tile_checks(t_map *map);
void		get_map_dimension(t_file_map *file_map);
int			check(t_map *map);
t_map		*init_map(t_file_map *file_map);
t_window	*init_window(void);
t_img		init_img(t_window *window);
bool		**init_bool_matrix(t_map *map);
void		free_boolean_matrix(bool **matrix, t_map *map);
void		find_path(t_map *map, bool **matrix, int x, int y);
int			flood_fill(t_map *map);
int			get_player_coordinates(t_map *tmp_map);
/*Graphics*/
void		set_window_dimensions(t_window *window, t_map *t_map);
void		create_window(t_window *window, t_map *map);
/*Sprite*/
void		put_sprite(t_window *window, int x, int y, void *sprite);
void		put_row(t_game *game, int base_x, int base_y, char *file);
void		init_sprites(t_game *game);
void		render_map_sprite(t_game *game, int pix_x, int pix_y);
/* Movement */
void		move_player_y(t_game *game, int px, int py, bool y);
void		move_player_up(t_game *game);
void		move_player_left(t_game *game);
void		move_player_right(t_game *game);
void		move_player_down(t_game *game);
int			on_player_event(int keycode, void *param);
void		print_move(t_game *game);
int			close_game(t_game *game);
void		setup_hooks(t_game *game);
int			win(t_game *game);
void		free_file_map(t_file_map *file_map);
void		free_map(t_map *map);
int			fail_and_clean(t_game *game, t_file_map *file_map);
void		free_sprites(t_game *game);
/* Extra *\
void		put_pixel(t_img *img, int base_x, int base_y, int color);
void		draw_circle(t_window *window, t_img *img,
int base_x, int base_y, int color);
void		draw_donut(t_window *window, t_img *img, int x, int y, int color);
void		draw_line(t_img *img, int base_x, int base_y, int color);
void		draw_tile(t_img *img, int base_x,
int base_y, int color);
void		draw_tiles_row(t_map *map, t_img *img,
int pixel_x, int pixel_y, int color);
void		draw_map_tiles(t_window *window, t_map *map,
t_img *img, int pixel_x, int pixel_y);
void		render(t_map *map, t_window *window,
int base_x, int base_y, int color);
void		draw_background_tiles(t_map *map, t_img *img,
int pixel_x, int pixel_y, int color);
void		render_wall(t_map *map, t_window *window,
int base_x, int base_y, int color);
void		draw_map_tiles(t_window *window, t_map *map,
t_img *img, int pixel_x, int pixel_y);
*/
#endif

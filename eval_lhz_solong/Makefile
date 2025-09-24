CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
XFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -I/usr/include -I$(MLX_DIR)
SRC_DIR = src/
MLX_DIR = src/mlx/
LIBFT_DIR = src/libft/
LIBFT = $(LIBFT_DIR)/libft.a

OBJECTS = $(SRC_DIR)main.o $(SRC_DIR)init.o $(SRC_DIR)file_check.o $(SRC_DIR)check.o \
		  $(SRC_DIR)map_check.o $(SRC_DIR)path_find.o $(SRC_DIR)init_graphics.o \
		  $(SRC_DIR)render.o $(SRC_DIR)move.o $(SRC_DIR)free_things.o \
		  $(SRC_DIR)get_next_line.o $(SRC_DIR)get_next_line_utils.o \
		  $(SRC_DIR)get_next_line_init.o $(SRC_DIR)utils.o 

all: so_long

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

so_long: $(OBJECTS) $(LIBFT)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBFT) $(XFLAGS)

.PHONY: clean fclean re

clean:
	rm -f so_long $(OBJECTS)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f so_long
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

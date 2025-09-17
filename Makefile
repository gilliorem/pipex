NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC_DIR = src
SRC = main.c free.c
OBJ = $(addprefix $(SRC_DIR)/,$(SRC:.c=.o))
INCLUDES = -Iinclude -Ilibft
FT_DIR = libft
FT_LIB = $(FT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(FT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(FT_LIB) -o $(NAME)

$(FT_LIB):
	$(MAKE) -C $(FT_DIR)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(FT_DIR) fclean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(FT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re


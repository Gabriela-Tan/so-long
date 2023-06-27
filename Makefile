NAME = so_long

SRC = 0_get_next_line.c \
	1_input_handling.c \
	2_map_error_handling.c \
	3_map_creation.c \
	4_player_moves.c \
	5_map_build.c \
	6_keyhook.c \
	7_init_game.c \
	8_end_game.c \
	9_window_image_handling.c

OBJECTS = $(SRC:.c=.o)
LIBFT_OBJ = ./include/libft/libft.a
MLX = ./include/minilibx/libmlx.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I./headers/

LIB =  $(MLX) -framework OpenGL -framework AppKit

$(NAME): $(OBJECTS) $(LIBFT_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB)

$(OBJECTS): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

$(LIBFT_OBJ):
	make --directory=./include/libft

all: $(NAME)

clean:
	rm -f $(OBJECTS)
	make clean -C ./include/libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./include/libft

re: fclean all

.PHONY: all clean fclean re

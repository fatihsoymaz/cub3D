NAME = cub3D

SRCS =  ./SRC/parser/utils.c ./SRC/parser/map_dup_ctrl.c ./SRC/parser/utils2.c \
        ./SRC/parser/ft_ret.c ./SRC/parser/map.c ./SRC/parser/main.c ./SRC/parser/sn_utils.c \
        ./SRC/parser/nswc_utils_1.c ./SRC/parser/map_control.c \
        ./SRC/parser/rgb_utils.c

GNL_SRCS = ./include/get_next_line/libftgnl.a
LIBFT_SRC = ./include/libft/libft.a

OBJS = $(SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRC:.c=.o)

MLX = ./include/mlx/libmlx.a
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LFLAGS = -framework OpenGL -framework AppKit -L./include/mlx -lmlx

CC=gcc

all: $(MLX) $(NAME) $(OBJS) $(GNL_OBJS) $(LIBFT_OBJS)

$(NAME): $(MLX) $(OBJS) $(GNL_OBJS) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT_OBJS) -o $(NAME)

$(MLX):
	$(MAKE) -C ./include/mlx

$(GNL_OBJS):
	@make -C ./include/get_next_line

$(LIBFT_OBJS):
	@make -C ./include/libft

clean:
	@rm -rf $(OBJS)

fclean: clean
	@make clean -C ./include/get_next_line
	@make clean -C ./include/libft
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

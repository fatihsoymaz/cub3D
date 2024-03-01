NAME = cub3D
SRCS =  ./SRC/parser/utils.c ./SRC/parser/map_dup_ctrl.c ./SRC/parser/utils2.c \
		./SRC/parser/ft_ret.c ./SRC/parser/map.c ./SRC/parser/main.c ./SRC/parser/sn_utils.c \
		./SRC/parser/nswc_utils_1.c ./SRC/parser/map_control.c \
		./SRC/parser/rgb_utils.c \
		./include/get_next_line/libftgnl.a ./include/libft/libft.a
OBJS = $(SRCS:.c=.o)
LIBFT = ./include/libft/libft.a
GNL_SRCS = ./include/get_next_line/libftgnl.a
GNL_OBJS = $(GNL_SRCS:.c=.o)
LIBFT_SRC = ./include/libft/libft.a
LIBFT_OBJS = $(LIBFT_SRC:.=.o)
MLX = ./include/mlx/libmlx.a
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LFLAGS = -framework OpenGL -framework AppKit -L./include/mlx -lmlx

CC=gcc

all: $(MLX) $(NAME) $(OBJS) $(GNL_OBJS) $(LIBFT_OBJS)

$(LIBFT):
	$(MAKE) -C ./include/libft

$(NAME): $(MLX) $(OBJS) $(GNL_OBJS)
		gcc $(CFLAGS) $(LFLAGS) $(OBJS) $(GNL_OBJS) -o $(NAME)
$(MLX):
	$(MAKE) -C ./include/mlx
$(GNL_OBJS):
	@make -C ./include/get_next_line


clean:
	@rm -rf $(OBJS)
fclean: clean
	  make clean -C ./include/get_next_line
	# make clean -C ./include/mlx
	  make clean -C ./include/libft
	@rm -rf $(NAME)
re: fclean all

.PHONY: all bonus clean fclean re


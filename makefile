NAME = fdf
CC = gcc
SRC = main.c draw.c gnl/get_next_line.c gnl/get_next_line_utils.c parse.c project.c transformations.c \
controls.c
CFLAGS = -Wextra -Wall -Werror
OBJ = ${SRC:.c=.o}
MLX = ./mlx
LIBFT = ./libft
HEADERS = -I ./includes

GREEN = \x1b[32m
RESET = \033[0m
RED   = \x1b[31m

%.o: %.c
	@$(CC) -o $@ -c $< $(HEADERS)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Making mlx...$(RESET)"
	@$(MAKE) -C $(MLX)
	@mv mlx/libmlx.dylib .
	@echo "$(GREEN)Making libft...$(RESET)"
	@$(MAKE) -C $(LIBFT)
	@mv libft/libft.a .
	@echo "$(GREEN)Compiling...$(RESET)"
	@$(CC) $(SRC) $(HEADERS) libmlx.dylib libft.a -fsanitize=address -o $(NAME)
	@echo "$(GREEN)Done!$(RESET)"

clean:
	@echo "$(RED)Cleaning...$(RESET)"
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(MLX) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f libmlx.dylib libft.a

re: fclean all


.PHONY: clean, all, fclean, re
NAME = fdf
CC = gcc
SRC = main.c draw.c parse.c project.c transformations.c controls.c
CFLAGS = -Wextra -Wall -Werror
OBJ = ${SRC:.c=.o}
MLXDIR = ./mlx
LIBFTDIR = ./libft
HEADERS = -I ./includes

GREEN = \x1b[32m
RESET = \033[0m
RED   = \x1b[31m

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

all: libmlx libft $(NAME)

libmlx:
	@echo "$(GREEN)Making mlx...$(RESET)"
	@$(MAKE) -C $(MLXDIR)
	@mv mlx/libmlx.dylib .

libft:
	@echo "$(GREEN)Making libft...$(RESET)"
	@$(MAKE) -C $(LIBFTDIR)
	@mv libft/libft.a .

$(NAME): $(OBJ)
	@echo "$(GREEN)Compiling...$(RESET)"
	@$(CC) $(CFLAGS) $(SRC) $(HEADERS) libmlx.dylib libft.a -o $(NAME)
	@echo "$(GREEN)Done!$(RESET)"

clean:
	@echo "$(RED)Cleaning...$(RESET)"
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFTDIR) clean
	@$(MAKE) -C $(MLXDIR) clean
	@echo "$(RED)Done!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -f libmlx.dylib libft.a

re: fclean all


.PHONY: clean, all, fclean, re, libmlx, libft
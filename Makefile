NAME = fdf
LIBFT = libft.a
LIBFT_DIR = libft
MINILIBX = libmlx.a
MINILIBX_DIR = mlx
CFLAGS = -Wall -Wextra -Werror
CFILES = controls.c draw.c exit.c ft_atoi_base.c init.c main.c utils.c
OFILES = ${CFILES:.c=.o}

all: $(NAME)

%o: %c 
	cc ${CFLAGS} -c $< -o ${<:.c=.o}

# $(NAME): $(LIBFT) $(OFILES) $(MINILIBX)
$(NAME): $(LIBFT) $(OFILES)
	cc $(CFLAGS) $(OFILES) -o $(NAME) -L $(LIBFT_DIR) -lft -L $(MINILIBX_DIR) -lmlx -lm -framework OpenGL -framework AppKit

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

clean: 
	rm -f $(OFILES)
	make -C $(LIBFT_DIR) clean
	
# make -C $(MINILIBX_DIR) clean // temp

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	
# rm -f $(MINILIBX_DIR)/$(MINILIBX) // temp

re: fclean all

test: 
	cc test.c -L $(MINILIBX_DIR) -lmlx -framework OpenGL -framework AppKit -o test

.PHONY: all clean fclean re 


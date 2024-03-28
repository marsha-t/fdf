NAME = fdf
LIBFT = libft.a
LIBFT_DIR = libft
MINILIBX = libmlx.a
MINILIBX_DIR = mlx
CFLAGS = -Wall -Wextra -Werror
CFILES = controls.c main.c draw.c\
	exit.c ft_atoi_base.c init.c utils.c line.c rotations.c colour.c parse_utils.c parse_checks.c parse_lines.c dimensions.c 
OFILES = ${CFILES:.c=.o}
BONUS_NAME = fdf_bonus
BONUS_CFILES = controls_bonus.c main_bonus.c draw_bonus.c\
	exit.c ft_atoi_base.c init.c utils.c line.c rotations.c colour.c parse_utils.c parse_checks.c parse_lines.c dimensions.c 
BONUS_OFILES = ${BONUS_CFILES:.c=.o}

all: $(NAME)

%o: %c 
	cc ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(LIBFT) $(OFILES) $(MINILIBX)
	cc $(CFLAGS) $(OFILES) -o $(NAME) -L $(LIBFT_DIR) -lft -L $(MINILIBX_DIR) -lmlx -lm -framework OpenGL -framework AppKit

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

bonus: $(LIBFT) $(BONUS_OFILES) $(MINILIBX)
	cc $(CFLAGS) $(BONUS_OFILES) -o $(BONUS_NAME) -L $(LIBFT_DIR) -lft -L $(MINILIBX_DIR) -lmlx -lm -framework OpenGL -framework AppKit

clean: 
	rm -f $(OFILES) $(BONUS_OFILES)
	make -C $(LIBFT_DIR) clean
	make -C $(MINILIBX_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	make -C $(LIBFT_DIR) fclean
	rm -f $(MINILIBX_DIR)/$(MINILIBX)

re: fclean all

.PHONY: all clean fclean re bonus


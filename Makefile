SRCS = main.c helper_function/get_next_line/get_next_line.c helper_function/get_next_line/get_next_line_utils.c \
	helper_function/ft_split.c parsing/main_parsing.c helper_function/ft_strtrim.c helper_function/ft_strlen.c \
	helper_function/ft_strchr.c helper_function/ft_strcmp.c helper_function/ft_strdup.c helper_function/ft_atoi.c \
	helper_function/garbage.c parsing/filename.c parsing/error_msg.c parsing/storing_map.c parsing/storing_elements.c \
	helper_function/extra_functions.c parsing/checking_map.c parsing/storing_colors.c raycast.c movement.c texture.c dda.c\
	helper_function/ft_memset.c helper_function/ft_calloc.c minimap.c init_game.c render.c init_struct.c

NAME = cub3d

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

MLBX = -Lminilibx-linux -l:libmlx_Linux.a -lX11 -lXext

CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(MLBX) -lm -o $(NAME) 

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJS)

re: fclean all

.SECONDARY: $(OBJS)
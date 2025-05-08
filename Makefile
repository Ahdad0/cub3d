SRCS = main.c helper_function/get_next_line/get_next_line.c helper_function/get_next_line/get_next_line_utils.c \
	helper_function/ft_split.c parsing/main_parsing.c

NAME = cub3d

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

MLBX = -Lminilibx-linux -l:libmlx_Linux.a -lX11 -lXext

CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(MLBX) -o $(NAME) 

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJS)

re: fclean all

.SECONDARY: $(OBJS)
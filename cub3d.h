#ifndef TEST
#define TEST

# include "helper_function/get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include "helper_functions.h"
// # include <mlx.h>
// # include <X11/X.h>
// # include <X11/keysym.h>
# include <stdio.h>
#include <stdbool.h>

typedef struct player
{
	int	x;
	int	y;
	char	*path_NO;
	char	*path_SO;
	char	*path_WE;
	char	*path_EA;
	void	**NO;
	void	**SO;
	void	**WE;
	void	**EA;
	int		*C_RGB;
	int		*F_RGB;
}	t_player;

typedef struct data
{
	int		index_player;
	int		index_checking;
	int		last_line;
	int		x;
	int		y;
	int		bits;
	int		size_line;
	int		endian;
	char	*dataa;
	void	*mlx;
	void	*mlx_win;
	char	**cpy_map;
	char	**cpy_map_parsing;
	char	**map;
	t_player	*player;
}	t_data;

void checking_filename(char **av);
int	*split_colors(t_data *data, char *line);
void	ft_write_stderr(t_data *data, char *string);
void	free_everything(t_data *data);
void	store_map(t_data *data, char **av);
void parsing(t_data *data, char **av);
int	position_of_char(char *string, char *c);
void	store_element(t_data *data);
int	len_matrix(char **array);
char	**two_arguments(char *one_line);
void	free_mat(char **arr);
void	store_oriandcpy_map(t_data *data);
void	check_path_elements(t_data *data);
void	checking_map(t_data *data);

#endif
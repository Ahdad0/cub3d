#ifndef TEST
#define TEST

// #define MOVE_UP 119 //W
// #define MOVE_UP 97 //A
// #define MOVE_UP 115 //S
// #define MOVE_UP 100 //D
// #define ECHAP 65307 

#define MOVE_UP 119 //Z
#define MOVE_LEFT 97 //Q
#define MOVE_DOWN 115 //S
#define MOVE_RIGHT 100 //D
#define ECHAP 65307 


#define KEY_PRESS        2
#define KEY_RELEASE      3
#define KEY_PRESS_MASK   (1L << 0)
#define KEY_RELEASE_MASK (1L << 1)

#define TURN_LEFT  65361  // ou KEY_LEFT
#define TURN_RIGHT 65363  // ou KEY_RIGHT

# include "helper_function/get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include "helper_functions.h"
// # include <mlx.h>
// # include <X11/X.h>
// # include <X11/keysym.h>
# include <stdio.h>
#include <stdbool.h>
#include <math.h> 

typedef struct s_texture
{
    void   *img;
    char   *addr; 
    int     width;
    int     height;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_texture;

typedef struct player
{
	int		door_hide;
	int		press_x;
	double	x;
	double	y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	int turn_right;
	int turn_left;
	int move_up;
	int move_down;
	int move_right;
	int move_left;
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
	char dir;
	t_texture *textu;
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
	void *map_img;
	char *map_addr;
	int screen_w;
    int screen_h;
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
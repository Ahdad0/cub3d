#ifndef TEST
#define TEST

// #define MOVE_UP 119 //W
// #define MOVE_UP 97 //A
// #define MOVE_UP 115 //S
// #define MOVE_UP 100 //D
// #define ECHAP 65307 

#define MOVE_UP 122 //Z
#define MOVE_LEFT 113 //Q
#define MOVE_DOWN 115 //S
#define MOVE_RIGHT 100 //D
#define ECHAP 65307 

#include <stdbool.h>

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT  640
#define TILE_MMAP 20
#define SPEED 0.05
#define ROT_SPEED 0.03
#define PLAYER_SIZE  (TILE_MMAP/2) // côté du carré en pixels
// #define PLAYER_RADIUS ((double)PLAYER_SIZE / TILE_MMAP / 2.0) 
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

typedef struct  s_img
{
    void    *img;
    char    *addr;
    int      bits_per_pixel;
    int      line_length;
    int      endian;
}               t_img;

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

enum e_texindex 
{ 
	NORTH = 0, 
	SOUTH = 1, 
	WEST = 2, 
	EAST = 3 
};

typedef struct  s_tex_data
{
    int     index;
    int     x;
    int     y;
    int     size;
    double  step;
    double  pos;
    int     hex_ceiling;
    int     hex_floor;
}               t_tex_data;

typedef struct  s_ray
{
    double  camera_x;
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    double  deltadist_x;
    double  deltadist_y;
    double  sidedist_x;
    double  sidedist_y;
    int     step_x;
    int     step_y;
    int     side;
    double  wall_dist;
    int     line_height;    
    int     draw_start;
    int     draw_end;
    double  wall_x;
}               t_ray;

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
	t_player	*player;
	 int     win_width;
    int     win_height;

    int    **texture_pixels;
    int    **textures;
    int      tex_size;

    t_tex_data tex_data;  
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

//init

void init_mlx_win_and_img(t_data *data);
void	compute_ceil_floor_colors(t_data *data);
void	init_game(t_data *data, char **av);
void	allocate_texture_buffer(t_data *data);
void	setup_mlx_loop(t_data *data);
void	initilaze_struct(t_data *data);
void	init_texture_fields(t_data *data);

//texture
void    initialize_texture(t_data *data);
void texture_id(t_data *data, t_ray *ray);
void    fill_column_with_texture(t_data *data, t_tex_data *tex, t_ray *ray, int x);
void    load_one_texture(t_data *data, int index, char *path);
void    load_all_textures(t_data *data);

//movement
int key_press(int keycode, t_data *d);
int key_release(int keycode, t_data *d);
void update_player_rotation(t_data *d);
void update_player_pos(t_data *d);

//dda_1
void	init_ray_side_x(t_ray *ray, t_player *player);
void	init_ray_side_y(t_ray *ray, t_player *player);
void dda_init(t_ray *ray, t_player *player);
void	advance_ray_step(t_ray *ray);
int	check_collision_or_exit(t_data *data, t_ray *ray);

//dda_2
void dda_advance_ray_to_collision(t_data *data, t_ray *ray);
void	calculate_wall_distance(t_ray *ray);
void	calculate_wall_x(t_ray *ray, t_player *player);
void	get_line_bounds(t_ray *ray, t_data *data);
void get_wall_line_height(t_ray *ray, t_data *data, t_player *player);

//raycasting
void init_raycast(int x, t_ray *ray, t_player *player, t_data *data);
int raycasting(t_player *player, t_data *data);

//render
void draw_3d_to_img(t_data *data);
int render_loop3d(t_data *data);
void put_pixel_to_img(t_data *data, int px, int py, int color);

//minimap
void draw_minimap_on_image(t_data *data);

int close_window(t_data *data);

#endif
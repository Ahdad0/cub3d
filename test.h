#ifndef TEST
#define TEST

# include "helper_function/get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include "helper_functions.h"
// # include <mlx.h>
// # include <X11/X.h>
// # include <X11/keysym.h>
# include <stdio.h>

typedef struct player
{
	int	x;
	int	y;
	void	*player_image;
	void	*view;
	void	*floor_image;
}	t_player;

typedef struct data
{
	int		x;
	int		y;
	int		bits;
	int		size_line;
	int		endian;
	char	*dataa;
	void	*mlx;
	void	*mlx_win;
	char	**map;
	t_player	*player;
}	t_data;

#endif
#include "cub3d.h"

void	init_paths_and_colors(t_data *data)
{
	data->player->path_NO = NULL;
	data->player->path_SO = NULL;
	data->player->path_WE = NULL;
	data->player->path_EA = NULL;
	data->player->NO      = NULL;
	data->player->SO      = NULL;
	data->player->WE      = NULL;
	data->player->EA      = NULL;
	data->player->C_RGB   = NULL;
	data->player->F_RGB   = NULL;
}

void	init_map_and_player_state(t_data *data)
{
	data->x = 0;
	data->y = 0;
	data->player->x         = 0;
	data->player->y         = 0;
	data->player->move_up    = 0;
	data->player->move_down  = 0;
	data->player->move_left  = 0;
	data->player->move_right = 0;
	data->player->dir_x      = 1.0;
	data->player->dir_y      = 0.0;
	data->player->plane_x    = 0.0;
	data->player->plane_y    = 0.66;
	data->player->turn_left  = 0;
	data->player->turn_right = 0;
}

void	init_texture_fields(t_data *data)
{
	data->texture_pixels = NULL;
	data->textures       = NULL;
	data->tex_size       = 64;
	data->tex_data.orientation  = 0;
	data->tex_data.size   = data->tex_size;
}

void	initilaze_struct(t_data *data)
{
	init_paths_and_colors(data);
	init_map_and_player_state(data);
	init_texture_fields(data);
}

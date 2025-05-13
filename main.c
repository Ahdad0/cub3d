#include "cub3d.h"
#include <stdbool.h>
#include <ctype.h>

void	initilaze_struct(t_data *data)
{
	data->player->path_NO = NULL;
	data->player->path_SO = NULL;
	data->player->path_WE = NULL;
	data->player->path_EA = NULL;
	data->player->C_RGB = NULL;
	data->player->F_RGB = NULL;
	data->x = 0;
	data->y = 0;
	data->player->y = 0;
	data->player->x = 0;
}

int main(int ac, char **av)
{
	t_data *data;
	t_player player;
	// int		height;
	// int		wight;

	if (ac != 2)
		ft_write_stderr("run it with : ./cub3d maps/map.cub");
	else
		checking_filename(av);
	// data = malloc(sizeof(t_data));
	data = alloc(sizeof(t_data), ALLOC);
	data->player = &player;
	data->mlx = mlx_init();
	initilaze_struct(data);
	parsing(data, av);
	// int x = 0;
	// data->mlx_win = mlx_new_window(data->mlx, data->x * 64, data->y * 64, "New");
	// printf("data=%s-\n", dataa);
	// data->player->view = mlx_new_image(data->mlx, 63, 63);
	// data->dataa = mlx_get_data_addr(data->player->view, &data->bits, &data->size_line, &data->endian);
	// put_image(data);
	// mlx_put_image_to_window(data->mlx, data->mlx_win,
	// 			data->player->player_image, data->player->x * 64, data->player->y * 64);
	// mlx_hook(data->mlx_win, 2, 17, key_press, data);
	// mlx_hook(data->mlx_win, 17, 1L<<17, close_window, NULL);
	// mlx_loop(data->mlx);
}
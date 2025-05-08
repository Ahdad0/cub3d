#include "cub3d.h"
#include <stdbool.h>
#include <ctype.h>




int main(int ac, char **av)
{
	t_data *data;
	t_player player;
	// int		height;
	// int		wight;

	(void)ac;
	data = malloc(sizeof(t_data));
	data->player = &player;
	data->mlx = mlx_init();
	calculate(data, av);
	storing_info(data);
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
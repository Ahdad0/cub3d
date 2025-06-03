#include "cub3d.h"

void init_mlx_win_and_img(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_write_stderr(data, "Error: cannot init MLX");
	data->mlx_win = mlx_new_window(data->mlx, data->win_width, data->win_height, "cub3D");
	if (!data->mlx_win)
		ft_write_stderr(data, "Error: cannot create window");
	data->map_img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!data->map_img)
		ft_write_stderr(data, "Error: cannot create image");
	data->map_addr = mlx_get_data_addr(data->map_img, &data->bits, &data->size_line, &data->endian);
}

void	compute_ceil_floor_colors(t_data *data)
{
	int r;
	int g;
	int b;

	r = data->player->C_RGB[0];
	g = data->player->C_RGB[1];
	b = data->player->C_RGB[2];
	data->texinfo.hex_ceiling = (r << 16) | (g << 8) | b;
	r = data->player->F_RGB[0];
	g = data->player->F_RGB[1];
	b = data->player->F_RGB[2];
	data->texinfo.hex_floor = (r << 16) | (g << 8) | b;
}

void	init_game(t_data *data, char **av)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit(1);
	data->win_width = SCREEN_WIDTH;
	data->win_height = SCREEN_HEIGHT;
	initilaze_struct(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_write_stderr(data, "Error: cannot init MLX");
	data->mlx_win = mlx_new_window( data->mlx, data->win_width, data->win_height, "cub3D");
	if (!data->mlx_win)
		ft_write_stderr(data, "Error: cannot create window");
	data->map_img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!data->map_img)
		ft_write_stderr(data, "Error: cannot create image");
	data->map_addr = mlx_get_data_addr(data->map_img, &data->bits, &data->size_line, &data->endian);
	parsing(data, av);
	compute_ceil_floor_colors(data);
	data->tex_size = 64;
	load_all_textures(data);
}

void	allocate_texture_buffer(t_data *data)
{
	int y;

	data->texture_pixels = ft_calloc(data->win_height, sizeof(int *));
	if (!data->texture_pixels)
		ft_write_stderr(data, "Error: malloc texture_pixels");
	y = 0;
	while (y < data->win_height)
	{
		data->texture_pixels[y] = ft_calloc(data->win_width, sizeof(int));
		if (!data->texture_pixels[y])
			ft_write_stderr(data, 
				"Error: malloc texture_pixels row");
		y++;
	}
}

void	setup_mlx_loop(t_data *data)
{
	mlx_loop_hook(data->mlx, render_loop3d, data);
	mlx_hook(data->mlx_win, KEY_PRESS, KEY_PRESS_MASK, key_press, data);
	mlx_hook(data->mlx_win, KEY_RELEASE, KEY_RELEASE_MASK, key_release, data);
	mlx_hook(data->mlx_win, 17, 0, close_window, data);
}

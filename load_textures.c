#include "cub3d.h"

void	load_one_texture(t_data *data, int index, char *path)
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		i;
	int		size;

	img = mlx_xpm_file_to_image(data->mlx, path, &data->tex_size, &data->tex_size);
	if (!img)
		ft_write_stderr(data, "Error: impossible de charger texture");
	addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	size = data->tex_size * data->tex_size;
	data->textures[index] = malloc(sizeof(int) * size);
	if (!data->textures[index])
		ft_write_stderr(data, "Error: malloc textures");
	i = 0;
	while (i < size)
	{
		data->textures[index][i] = *(unsigned int *)
		(addr + (i / data->tex_size) * line_len + (i % data->tex_size) * (bpp / 8));
		i++;
	}
	mlx_destroy_image(data->mlx, img);
}

void	load_all_textures(t_data *data)
{
	data->textures = malloc(sizeof(int *) * 4);
	if (!data->textures)
		ft_write_stderr(data, "Error: malloc textures array");
	load_one_texture(data, NORTH, data->player->path_NO);
	load_one_texture(data, SOUTH, data->player->path_SO);
	load_one_texture(data, WEST,  data->player->path_WE);
	load_one_texture(data, EAST,  data->player->path_EA);
}

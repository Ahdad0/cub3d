#include "cub3d.h"

void	init_texture_pixels(t_data *data)
{
	int	i;

	if (data->texture_pixels)
	{
		i = 0;
		while (i < data->win_height)
		{
			free(data->texture_pixels[i]);
			i++;
		}
		free(data->texture_pixels);
	}

	data->texture_pixels = ft_calloc(data->win_height, sizeof(int *));
	if (!data->texture_pixels)
		ft_write_stderr(data, "Error: malloc texture_pixels");
	i = 0;
	while (i < data->win_height)
	{
		data->texture_pixels[i] = ft_calloc(data->win_width, sizeof(int));
		if (!data->texture_pixels[i])
			ft_write_stderr(data, "Error: malloc texture_pixels row");
		i++;
	}
}

void	get_texture_index(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			data->texinfo.index = WEST;
		else
			data->texinfo.index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			data->texinfo.index = SOUTH;
		else
			data->texinfo.index = NORTH;
	}
}

void	update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x)
{
	int	y;
	int	color;

	get_texture_index(data, ray);

	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_height;
	tex->pos  = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * tex->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = data->textures[tex->index][tex->size * tex->y + tex->x];
		if (color > 0)
			data->texture_pixels[y][x] = color;
		y++;
	}
}

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

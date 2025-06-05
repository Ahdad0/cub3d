#include "cub3d.h"

void	init_texture_fields(t_data *data)
{
	data->texture_pixels = NULL;
	data->textures       = NULL;
	data->tex_size       = 64;
	data->tex_data.orientation  = 0;
	data->tex_data.size   = data->tex_size;
}

static void	free_texture_pixels_if_exists(t_data *data)
{
	int	i;

	if (!data->texture_pixels)
		return ;
	i = 0;
	while (i < data->win_height)
	{
		free(data->texture_pixels[i]);
		i++;
	}
	free(data->texture_pixels);
	data->texture_pixels = NULL;
}

static void	allocate_texture_pixels_matrix(t_data *data)
{
	int	i;

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

void	initialize_texture(t_data *data)
{
	free_texture_pixels_if_exists(data);
	allocate_texture_pixels_matrix(data);
}

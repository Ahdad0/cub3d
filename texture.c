#include "cub3d.h"

void	texture_orientation(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			data->tex_data.orientation = WEST;
		else
			data->tex_data.orientation = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			data->tex_data.orientation = SOUTH;
		else
			data->tex_data.orientation = NORTH;
	}
}

static void	compute_texture_x(t_data *data, t_tex_data *tex, t_ray *ray)
{
	texture_orientation(data, ray);
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
}

static void	compute_step_and_pos(t_data *data, t_tex_data *tex, t_ray *ray)
{
	tex->step = (double)tex->size / ray->line_height;
	tex->pos = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * tex->step;
}

static void	draw_textured_column(t_data *data, t_tex_data *tex, t_ray *ray, int x)
{
	int	y;
	int	color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = data->textures[tex->orientation][tex->size * tex->y + tex->x];
		if (color > 0)
			data->texture_pixels[y][x] = color;
		y++;
	}
}

void	fill_column_with_texture(t_data *data, t_tex_data *tex, t_ray *ray, int x)
{
	compute_texture_x(data, tex, ray);
	compute_step_and_pos(data, tex, ray);
	draw_textured_column(data, tex, ray, x);
}

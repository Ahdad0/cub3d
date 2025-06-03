#include "cub3d.h"

void	init_img(t_data *data, t_img *image, int w, int h)
{
	image->img = mlx_new_image(data->mlx, w, h);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length, &image->endian);
}

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	char *dst;

	dst = image->addr + (y * image->line_length) + (x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	int	color;

	
	color = data->texture_pixels[y][x];
	if (color > 0)
		set_image_pixel(image, x, y, color);
	else if (y < data->win_height / 2)
		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
	else
		set_image_pixel(image, x, y, data->texinfo.hex_floor);
}

void	init_raycasting_info(int x, t_ray *ray, t_player *player, t_data *data)
{
	ray->camera_x = 2 * x / (double)data->win_width - 1;
	ray->dir_x    = player->dir_x   + player->plane_x * ray->camera_x;
	ray->dir_y    = player->dir_y   + player->plane_y * ray->camera_x;
	ray->map_x    = (int)player->x;
	ray->map_y    = (int)player->y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

int	raycasting(t_player *player, t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < data->win_width)
	{
		init_raycasting_info(x, &ray, player, data);
		set_dda(&ray, player);
		perform_dda(data, &ray);
		calculate_line_height(&ray, data, player);
		update_texture_pixels(data, &data->texinfo, &ray, x);
		x++;
	}
	return (0);
}


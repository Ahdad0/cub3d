#include "cub3d.h"

void	init_raycast(int x, t_ray *ray, t_player *player, t_data *data)
{
	ray->map_x    = (int)player->x;
	ray->map_y    = (int)player->y;
	ray->camera_x = 2 * x / (double)data->win_width - 1;
	ray->dir_x    = player->dir_x   + player->plane_x * ray->camera_x;
	ray->dir_y    = player->dir_y   + player->plane_y * ray->camera_x;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);/**/
}

int	raycasting(t_player *player, t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < data->win_width)
	{
		init_raycast(x, &ray, player, data);
		dda_init(&ray, player);
		dda_advance_ray_to_collision(data, &ray);
		get_wall_line_height(&ray, data, player);
		fill_column_with_texture(data, &data->tex_data, &ray, x);
		x++;
	}
	return (0);
}


#include "cub3d.h"

void	init_ray_side_x(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->x) * ray->deltadist_x;
	}
}

void	init_ray_side_y(t_ray *ray, t_player *player)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->y) * ray->deltadist_y;
	}
}

void	dda_init(t_ray *ray, t_player *player)
{
	init_ray_side_x(ray, player);
	init_ray_side_y(ray, player);
}

void	advance_ray_step(t_ray *ray)
{
	if (ray->sidedist_x < ray->sidedist_y)
	{
		ray->sidedist_x += ray->deltadist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->sidedist_y += ray->deltadist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

int	check_collision_or_exit(t_data *data, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= data->x
		|| ray->map_y < 0 || ray->map_y >= data->y)
		return (1);
	if (data->map[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

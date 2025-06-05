#include "cub3d.h"

static void	init_ray_side_x(t_ray *ray, t_player *player)
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

static void	init_ray_side_y(t_ray *ray, t_player *player)
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

static void	advance_ray_step(t_ray *ray)
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

static int	check_collision_or_exit(t_data *data, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= data->x
		|| ray->map_y < 0 || ray->map_y >= data->y)
		return (1);
	if (data->map[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

void	dda_advance_ray_to_collision(t_data *data, t_ray *ray)
{
	while (1)
	{
		advance_ray_step(ray);
		if (check_collision_or_exit(data, ray))
			break;
	}
}

static void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = ray->sidedist_x - ray->deltadist_x;
	else
		ray->wall_dist = ray->sidedist_y - ray->deltadist_y;
}

static void	calculate_wall_x(t_ray *ray, t_player *player)
{
	double	raw_wall_x;

	if (ray->side == 0)
		raw_wall_x = player->y + ray->wall_dist * ray->dir_y;
	else
		raw_wall_x = player->x + ray->wall_dist * ray->dir_x;
	
	ray->wall_x = raw_wall_x - floor(raw_wall_x);
}

static void	get_line_bounds(t_ray *ray, t_data *data)
{
	int	h;
	int	h_half;

	h = (int)(data->win_height / ray->wall_dist);
	ray->line_height = h;
	h_half = h / 2;
	ray->draw_start = -h_half + (data->win_height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = h_half + (data->win_height / 2);
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
}

void	get_wall_line_height(t_ray *ray, t_data *data, t_player *player)
{
	calculate_wall_distance(ray);
	get_line_bounds(ray, data);
	calculate_wall_x(ray, player);
}

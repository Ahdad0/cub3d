#include "cub3d.h"

void set_dda(t_ray *ray, t_player *player)
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

void perform_dda(t_data *data, t_ray *ray)
{
    int hit = 0;

    while (hit == 0)
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
        if (ray->map_x < 0 || ray->map_x >= data->x
         || ray->map_y < 0 || ray->map_y >= data->y)
            break;
        if (data->map[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }
}

void calculate_line_height(t_ray *ray, t_data *data, t_player *player)
{
    if (ray->side == 0)
        ray->wall_dist = ray->sidedist_x - ray->deltadist_x;
    else
        ray->wall_dist = ray->sidedist_y - ray->deltadist_y;

    ray->line_height = (int)(data->win_height / ray->wall_dist);
    ray->draw_start  = -ray->line_height / 2 + data->win_height / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + data->win_height / 2;
    if (ray->draw_end >= data->win_height)
        ray->draw_end = data->win_height - 1;

    if (ray->side == 0)
        ray->wall_x = player->y + ray->wall_dist * ray->dir_y;
    else
        ray->wall_x = player->x + ray->wall_dist * ray->dir_x;
    ray->wall_x -= floor(ray->wall_x);
}

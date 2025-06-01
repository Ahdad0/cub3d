/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahaded <abahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:56 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/30 07:12:55 by abahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <ctype.h>
#include <stdbool.h>

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT  640
#define TILE_MMAP 20
#define SPEED 0.05
#define ROT_SPEED 0.1
#define PLAYER_SIZE  (TILE_MMAP/2) // côté du carré en pixels
// #define PLAYER_RADIUS ((double)PLAYER_SIZE / TILE_MMAP / 2.0) 

void render3d(t_data *d);
void draw_vertical_line(t_data *d, int x, int start, int end, int side);
void draw_minimap(t_data *d);

void	initilaze_struct(t_data *data)
{
	data->player->door_hide = 0;
	data->player->press_x = 0;
	data->player->path_NO = NULL;
	data->player->path_SO = NULL;
	data->player->path_WE = NULL;
	data->player->path_EA = NULL;
	data->player->NO = NULL;
	data->player->SO = NULL;
	data->player->WE = NULL;
	data->player->EA = NULL;
	data->player->C_RGB = NULL;
	data->player->F_RGB = NULL;
	data->x = 0;
	data->y = 0;
	data->player->y = 0;
	data->player->x = 0;
	data->player->move_up    = 0;
	data->player->move_down  = 0;
	data->player->move_left  = 0;
	data->player->move_right = 0;
	data->cpy_map_parsing = NULL;
	data->map_img = NULL;
	data->map_addr = NULL;
	
	data->player->dir_x   = 1.0;
    data->player->dir_y   = 0.0;
    data->player->plane_x = 0.0;
    data->player->plane_y = 0.66;
    data->player->turn_left  = 0;
    data->player->turn_right = 0;
	
	data->screen_w = SCREEN_WIDTH;
	data->screen_h = SCREEN_HEIGHT;
	// data->press_x = 0;
}

int close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	if(data->mlx)
		free(data->mlx);
	exit(0);
	return(0);
}

void put_pixel_to_img(t_data *data, int px, int py, int color)
{
	char *dst;
    
	dst = data->map_addr 
	+ (py * data->size_line) //décalage y
	+ (px * (data->bits / 8)); //décalage x
	*(unsigned int *)dst = color; // 4bytes pour endian
}

void draw_rect_img(t_data *data, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < TILE_MMAP)
	{
		j = 0;
		while(j < TILE_MMAP)
		{
			put_pixel_to_img(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void draw_player(t_data *data)
{
    int size = TILE_MMAP / 2;
    int half = size / 2;
    int px = (int)(data->player->x * TILE_MMAP) - half;
    int py = (int)(data->player->y * TILE_MMAP) - half;
    int y = 0;

    while (y < size)
    {
        int x = 0;
        while (x < size)
        {
            put_pixel_to_img(data, px + x, py + y, 0x00FF00);
            x++;
        }
        y++;
    }
}


void draw_map_to_img(t_data *data)
{
	int x;
	int y;
	int tx;
	int ty;
	
	tx = 0;
	ty = 0;
	x = 0;
	y = 0;
	while(y < data->y)
	{
		x = 0;
		while(x < data->x)
		{
			tx = x * TILE_MMAP;
			ty = y * TILE_MMAP;
			if(!data->map[y] || !data->map[y] || !data->map[y][x])
				break;
			if(data->map[y][x] == '1')
				draw_rect_img(data, tx, ty, 0x555555);
			else if (data->map[y][x] == 'D')
				draw_rect_img(data, tx, ty, 0x555555);
			// else if(data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x] == 'E' || data->map[y][x] == 'W')
			// 	draw_rect_img(data, tx, ty, 0xFF0000);
			else
				draw_rect_img(data, tx, ty, 0xDDDDDD);
			x++;
		}
		y++;
	}
}

int key_press(int keycode, t_data *d)
{
	printf("%d\n", keycode);
	d->player->press_x = 0;
	if(keycode == MOVE_UP)
		d->player->move_up = 1;
	if(keycode == MOVE_DOWN)
		d->player->move_down = 1;
	if(keycode == MOVE_RIGHT)
		d->player->move_right = 1;
	if(keycode == MOVE_LEFT)
		d->player->move_left = 1;
	if(keycode == TURN_LEFT)
		d->player->turn_left = 1;
	if(keycode == TURN_RIGHT)
		d->player->turn_right = 1;
	if (keycode == 120)
	{
		d->player->press_x = 1;
	}
	if (keycode == ECHAP) 
		close_window(d);
	return(0);
}

int key_release(int keycode, t_data *d)
{
	if(keycode == MOVE_UP)
		d->player->move_up = 0;
	if(keycode == MOVE_DOWN)
		d->player->move_down = 0;
	if(keycode == MOVE_RIGHT)
		d->player->move_right = 0;
	if(keycode == MOVE_LEFT)
		d->player->move_left = 0;
	if(keycode == TURN_LEFT)
		d->player->turn_left = 0;
	if(keycode == TURN_RIGHT)
		d->player->turn_right = 0;
	return(0);
}

static void update_player_rotation(t_data *d)
{
    double old_dx = d->player->dir_x;
    double old_px = d->player->plane_x;
    double rs     = ROT_SPEED; //vitesse de rotation

    if (d->player->turn_left)
    {
        double c = cos(-rs);
        double s = sin(-rs);
        d->player->dir_x   = old_dx * c - d->player->dir_y * s;
        d->player->dir_y   = old_dx * s + d->player->dir_y * c;
        d->player->plane_x = old_px * c - d->player->plane_y * s;
        d->player->plane_y = old_px * s + d->player->plane_y * c;
    }
    if (d->player->turn_right)
    {
        double c = cos(rs);
        double s = sin(rs);
        d->player->dir_x   = old_dx * c - d->player->dir_y * s;
        d->player->dir_y   = old_dx * s + d->player->dir_y * c;
        d->player->plane_x = old_px * c - d->player->plane_y * s;
        d->player->plane_y = old_px * s + d->player->plane_y * c;
    }
}

void update_player_pos(t_data *d)
{
    double speed = SPEED;
    double nx = d->player->x;
    double ny = d->player->y;
	
    if (d->player->move_up)
    {
        nx += d->player->dir_x * speed;
        ny += d->player->dir_y * speed;
    }
    if (d->player->move_down)
    {
        nx -= d->player->dir_x * speed;
        ny -= d->player->dir_y * speed;
    }
    if (d->player->move_right)
    {
        nx += d->player->plane_x * speed;
        ny += d->player->plane_y * speed;
    }
    if (d->player->move_left)
    {
        nx -= d->player->plane_x * speed;
        ny -= d->player->plane_y * speed;
    }
	// int a = 0;
    int tx = (int)nx;
    int ty = (int)ny;
    if (tx < 0 || tx >= d->x || ty < 0 || ty >= d->y)
	{
        return;
	}
	// printf("key of x is %d\n", d->player->press_x);
	// printf("im in %c\n", d->map[ty][tx]);
	// if (((d->map[ty][tx + 1] == 'D') || 
    //  	(d->map[ty][tx - 1] == 'D') || 
    //  	(d->map[ty + 1] && d->map[ty + 1][tx] == 'D') || 
    //  	(ty - 1 >= 0 && d->map[ty - 1][tx] == 'D')) &&
    // if (d->map[ty][tx + 1] == 'D'
    //     && d->player->press_x == 1 && d->player->door_hide == 1)
	// {
	// 	printf("here!! doors closed\n");
	// 	d->player->door_hide = 0;
	// 	a = 1;
	// }
	// if (((d->map[ty][tx + 1] == 'D') || 
    //  	(d->map[ty][tx - 1] && d->map[ty][tx - 1] == 'D') || 
    //  	(d->map[ty + 1] && d->map[ty + 1][tx] == 'D') || 
    //  	(ty - 1 >= 0 && d->map[ty - 1][tx] == 'D')) &&
    // 	(d->player->door_hide == 0 && a == 1))
    // if (d->map[ty][tx + 1] == 'D'
    //     && d->player->door_hide == 0 && a == 1)
	// {
	// 	d->player->press_x = 0;
	// 	a = 0;
	// 	return;
	// }
	// if (((d->map[ty][tx + 1] == 'D') || 
    //  	(d->map[ty][tx - 1] == 'D') || 
    //  	(d->map[ty + 1] && d->map[ty + 1][tx] == 'D') || 
    //  	(ty - 1 >= 0 && d->map[ty - 1][tx] == 'D')) &&
    // if (d->map[ty][tx + 1] == 'D'
    //     && d->player->press_x == 1 && d->player->door_hide == 0)
	// {
	// 	printf("here!! doors open\n");
	// 	d->player->door_hide = 1;
	// 	d->player->press_x = 0;
	// }
    if (d->map[ty][tx] == '1' || (d->map[ty][tx] == 'D' && d->player->door_hide == 0)) // stop hiting it
	{
        return;
	}
    d->player->x = nx;
    d->player->y = ny;
}

#define FOV (M_PI / 3.0)   // 60° de champ de vision

// static void draw_fov_2d(t_data *d)
// {
//     const int  rays = 300;
//     double      base_angle = atan2(d->player->dir_y, d->player->dir_x);
//     for (int i = 0; i < rays; i++)
//     {
//         double angle = base_angle - FOV/2
//                      + (double)i * (FOV / (rays - 1));
//         double dx = cos(angle), dy = sin(angle);
//         double px = d->player->x * TILE_MMAP;
//         double py = d->player->y * TILE_MMAP;
//         for (double t = 0; t < d->x * TILE_MMAP; t += 1.0)
//         {
//             int mx = (int)((px + dx * t) / TILE_MMAP);
//             int my = (int)((py + dy * t) / TILE_MMAP);
//             if (d->map[my][mx] == '1') break;
//             put_pixel_to_img(d,
//                 (int)(px + dx * t),
//                 (int)(py + dy * t),
//                 0x3399FF);
//         }
//     }
// }


// static void draw_ray_2d(t_data *d)
// {
//     double px = d->player->x * TILE_MMAP;
//     double py = d->player->y * TILE_MMAP;
//     double len = sqrt(d->player->dir_x * d->player->dir_x
//                     + d->player->dir_y * d->player->dir_y);
//     double dx = d->player->dir_x / len;
//     double dy = d->player->dir_y / len;
//     double step = 0.0;
//     while (1)
//     {
//         int mx = (int)((px + dx * step) / TILE_MMAP);
//         int my = (int)((py + dy * step) / TILE_MMAP);
//         if (d->map[my][mx] == '1')
//             break;
//         put_pixel_to_img(d,
//             (int)(px + dx * step),
//             (int)(py + dy * step),
//             0xFF0000);
//         step += 1.0;
//     }
// }

typedef struct  s_dda
{
    double  rayDirX;
    double  rayDirY;
    double  deltaDistX;
    double  deltaDistY;
    double  sideDistX;
    double  sideDistY;
    int     stepX;
    int     stepY;
    int     side;
}               t_dda;

void init_delta(double rayDirX, double rayDirY, t_dda *dda)
{
    dda->rayDirX = rayDirX;
    dda->rayDirY = rayDirY;
    dda->deltaDistX = fabs(1.0 / rayDirX);
    dda->deltaDistY = fabs(1.0 / rayDirY);
}

void setup_sideX(t_data *d, t_dda *dda)
{
    double posX;
    int    mapX;

    posX = d->player->x;
    mapX = (int)posX;
    if (dda->rayDirX < 0)
    {
        dda->stepX = -1;
        dda->sideDistX = (posX - mapX) * dda->deltaDistX;
    }
    else
    {
        dda->stepX = 1;
        dda->sideDistX = (mapX + 1.0 - posX) * dda->deltaDistX;
    }
}

void setup_sideY(t_data *d, t_dda *dda)
{
    double posY;
    int    mapY;

    posY = d->player->y;
    mapY = (int)posY;
    if (dda->rayDirY < 0)
    {
        dda->stepY = -1;
        dda->sideDistY = (posY - mapY) * dda->deltaDistY;
    }
    else
    {
        dda->stepY = 1;
        dda->sideDistY = (mapY + 1.0 - posY) * dda->deltaDistY;
    }
}

void init_dda(t_data *d, double rayDirX, double rayDirY, t_dda *dda)
{
    init_delta(rayDirX, rayDirY, dda);
    setup_sideX(d, dda);
    setup_sideY(d, dda);
}

void perform_dda(t_data *d, t_dda *dda, int *mapX, int *mapY)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        if (dda->sideDistX < dda->sideDistY)
        {
            dda->sideDistX += dda->deltaDistX;
            *mapX += dda->stepX;
            dda->side = 0;
        }
        else
        {
            dda->sideDistY += dda->deltaDistY;
            *mapY += dda->stepY;
            dda->side = 1;
        }
        if (*mapX < 0 || *mapX >= d->x || *mapY < 0 || *mapY >= d->y)
            break;
        if (d->map[*mapY][*mapX] == '1' || (d->map[*mapY][*mapX] == 'D' && d->player->door_hide == 0)) // draw it 3d
		{
			// if (d->map[*mapY][*mapX] == 'D' && d->player->press_x != 1)
            hit = 1;
		}
    }
}

double compute_perp_dist(t_data *d, t_dda *dda, int mapX, int mapY)
{
    double perpWallDist;

    if (dda->side == 0)
        perpWallDist = (mapX - d->player->x + (1 - dda->stepX) / 2.0)
            / dda->rayDirX;
    else
        perpWallDist = (mapY - d->player->y + (1 - dda->stepY) / 2.0)
            / dda->rayDirY;
    return perpWallDist;
}

void compute_draw_params(int screen_h, double perpDist, int *start, int *end)
{
    int lineHeight;

    lineHeight = (int)(screen_h / perpDist);
    *start = -lineHeight / 2 + screen_h / 2;
    *end   =  lineHeight / 2 + screen_h / 2;
    if (*start < 0)
        *start = 0;
    if (*end >= screen_h)
        *end = screen_h - 1;
}

void render3d(t_data *d)
{
    int     x;
    int     mapX; int mapY;
    t_dda   dda;
    int     drawStart;
    int     drawEnd;

    x = 0;
    while (x < d->screen_w)
    {
        double cameraX;

        cameraX = 2.0 * x / (double)d->screen_w - 1.0;
        dda.rayDirX = d->player->dir_x + d->player->plane_x * cameraX;
        dda.rayDirY = d->player->dir_y + d->player->plane_y * cameraX;
        mapX = (int)d->player->x;
        mapY = (int)d->player->y;
        init_dda(d, dda.rayDirX, dda.rayDirY, &dda);
        perform_dda(d, &dda, &mapX, &mapY);
        compute_draw_params(d->screen_h,
            compute_perp_dist(d, &dda, mapX, mapY),
            &drawStart, &drawEnd);
        draw_vertical_line(d, x, drawStart, drawEnd, dda.side);
        x++;
    }
}


static int  rgb_to_int(int *rgb)
{
    return ((rgb[0] & 0xFF) << 16)
         | ((rgb[1] & 0xFF) <<  8)
         |  (rgb[2] & 0xFF);
}

void draw_vertical_line(t_data *d, int x, int start, int end, int side)
{
    int   y     = 0;
    int   ceilc = rgb_to_int(d->player->C_RGB);
    int   floorc = rgb_to_int(d->player->F_RGB);

	//ceiling
    while (y < start)
        put_pixel_to_img(d, x, y++, ceilc);

    //wall
    while (y <= end)
    {
        int color = 0xAAAAAA;
        if (side == 1)
            color /= 2;
        put_pixel_to_img(d, x, y++, color);
    }

    //ground
    while (y < d->screen_h)
        put_pixel_to_img(d, x, y++, floorc);
}


void draw_minimap(t_data *d)
{
    int scale = TILE_MMAP / 2;
    int offX  = d->screen_w - d->x * scale;
    int offY  = d->screen_h - d->y * scale;
    int my = 0;

    while (my < d->y)
    {
        int mx = 0;
        while (mx < d->x)
        {
            int tx = offX + mx * scale;
            int ty = offY + my * scale;
            if (tx >= 0 && ty >= 0
             && tx + scale <= d->screen_w
             && ty + scale <= d->screen_h)
            {
                int col = (d->map[my][mx] == '1' || d->map[my][mx] == 'D') ? 0x555555 : 0xDDDDDD;
				
                draw_rect_img(d, tx, ty, col);
            }
            mx++;
        }
        my++;
    }
        int px    = offX + (int)(d->player->x * scale);
        int py    = offY + (int)(d->player->y * scale);
        int half  = 4;
        int dy    = -half;
        while (dy <= half)
        {
            int dx = -half;
            while (dx <= half)
            {
                put_pixel_to_img(d, px + dx, py + dy, 0xFF0000);
                dx++;
            }
            dy++;
        }
}



int render_loop3d(t_data *data)
{
    update_player_rotation(data);
    update_player_pos(data);
    render3d(data);
    draw_minimap(data);
    mlx_put_image_to_window(data->mlx, data->mlx_win,
                            data->map_img, 0, 0);
    return (0);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_player	player;
	if (ac != 2)
	{
		write(2, "run it with : ./cub3d maps/map.cub", 34);
		exit(1);
	}
	else
		checking_filename(av);
	data = alloc(sizeof(t_data), ALLOC);
	data->player = &player;
	data->mlx = mlx_init();
	
	initilaze_struct(data);
	parsing(data, av);

	data->mlx_win = mlx_new_window(data->mlx, data->screen_w, data->screen_h, "cub3d 3D");
	data->map_img  = mlx_new_image(data->mlx, data->screen_w, data->screen_h);
	data->map_addr = mlx_get_data_addr(data->map_img, &data->bits, &data->size_line, &data->endian);
	// draw_map_to_img(data);
	mlx_loop_hook(data->mlx, render_loop3d, data);
	mlx_hook(data->mlx_win, KEY_PRESS, KEY_PRESS_MASK, key_press,   data);
	mlx_hook(data->mlx_win, KEY_RELEASE, KEY_RELEASE_MASK, key_release, data);
	mlx_hook(data->mlx_win, 17, 0, close_window, data);
	mlx_loop(data->mlx);
	free_everything(data);
}
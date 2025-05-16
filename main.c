/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-kher <iel-kher@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:56 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/16 20:13:25 by iel-kher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <ctype.h>
#include <stdbool.h>

#define TILE_MMAP 20


void	initilaze_struct(t_data *data)
{
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
	data->cpy_map_parsing = NULL;
	data->map_img = NULL;
	data->map_addr = NULL;
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
			if(data->map[y][x] == '1')
				draw_rect_img(data, tx, ty, 0x555555);
			else
				draw_rect_img(data, tx, ty, 0xDDDDDD);
			x++;
		}
		y++;
	}
}

int render_loop2d(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->map_img, 0, 0);
	return(0);
}


void debug_print_map(t_data *data)
{
    int y;
    int x;

    printf("DEBUG : map size = %d cols x %d rows\n", data->x, data->y);

    y = 0;
    while (y < data->y)
    {
        if (data->map[y] == NULL)
        {
            printf("DEBUG : map[%d] is NULL!\n", y);
            y++;
            continue;
        }

        printf("Ligne %2d (len %2zu): ", y, strlen(data->map[y]));

        x = 0;
        while (x < data->x)
        {
            char c = data->map[y][x];
            if (c)
                putchar(c);
            else
                putchar('?');
            x++;
        }
        putchar('\n');
        y++;
    }
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_player	player;

	// int		height;
	// int		wight;
	if (ac != 2)
	{
		write(2, "run it with : ./cub3d maps/map.cub", 34);
		exit(1);
	}
	else
		checking_filename(av);
	// data = malloc(sizeof(t_data));
	data = alloc(sizeof(t_data), ALLOC);
	data->player = &player;
	data->mlx = mlx_init();
	initilaze_struct(data);
	parsing(data, av);
	debug_print_map(data);
	data->mlx_win = mlx_new_window(data->mlx, data->x * TILE_MMAP, data->y * TILE_MMAP, "cub3d - minimap");
	data->map_img = mlx_new_image(data->mlx, data->x * TILE_MMAP, data->y * TILE_MMAP);
	data->map_addr = mlx_get_data_addr(data->map_img, &data->bits, &data->size_line, &data->endian);
	draw_map_to_img(data);
	mlx_loop_hook(data->mlx, render_loop2d, data);
	mlx_hook(data->mlx_win, 17, 0, close_window, data);
	mlx_loop(data->mlx);
	free_everything(data);
	// int x = 0;
	// data->mlx_win = mlx_new_window(data->mlx, data->x * 64, data->y * 64,
	// "New");
	// printf("data=%s-\n", dataa);
	// data->player->view = mlx_new_image(data->mlx, 63, 63);
	// data->dataa = mlx_get_data_addr(data->player->view, &data->bits,
	// &data->size_line, &data->endian);
	// put_image(data);
	// mlx_put_image_to_window(data->mlx, data->mlx_win,
	// 			data->player->player_image, data->player->x * 64,
	// data->player->y * 64);
	// mlx_hook(data->mlx_win, 2, 17, key_press, data);
	// mlx_hook(data->mlx_win, 17, 1L<<17, close_window, NULL);
	// mlx_loop(data->mlx);
}

#include "cub3d.h"

void put_pixel_to_img(t_data *data, int px, int py, int color)
{
    char *dst;

    dst = data->map_addr
        + (py * data->size_line)//line
        + (px * (data->bits / 8));//bits or col
    *(unsigned int *)dst = color;//endian
}

void draw_3d_to_img(t_data *data)
{
    int x, y;
    int color;

    y = 0;
    while (y < data->win_height)
    {
        x = 0;
        while (x < data->win_width)
        {
            color = data->texture_pixels[y][x];
            if (color > 0)
                put_pixel_to_img(data, x, y, color);
            else if (y < data->win_height / 2)
                put_pixel_to_img(data, x, y, data->tex_data.hex_ceiling);
            else
                put_pixel_to_img(data, x, y, data->tex_data.hex_floor);
            x++;
        }
        y++;
    }
}

int render_loop3d(t_data *data)
{
    int y;
    int x;

    update_player_rotation(data);
    update_player_pos(data);
    y = 0;
    while (y < data->win_height)
    {
        x = 0;
        while (x < data->win_width)
        {
            data->texture_pixels[y][x] = 0;
            x++;
        }
        y++;
    }
    raycasting(data->player, data);
    draw_3d_to_img(data);
    draw_minimap_on_image(data);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->map_img, 0, 0);
    return (0);
}

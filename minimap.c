#include "cub3d.h"

void	draw_square(t_data *data, int x0, int y0, int size, int col)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_to_img(data, x0 + i, y0 + j, col);
			j++;
		}
		i++;
	}
}

static void	draw_tile_cell(t_data *data, int my, int mx, int scale, int offX, int offY)
{
	int	tx;
	int	ty;
	int	col;

	tx = offX + mx * scale;
	ty = offY + my * scale;
	if (tx < 0 || ty < 0 || tx + scale > data->win_width || ty + scale > data->win_height)
		return ;
	if (data->map[my][mx] == '1')
		col = 0x555555;
	else
		col = 0xDDDDDD;
	draw_square(data, tx, ty, scale, col);
}

void	draw_minimap_tiles(t_data *data, int scale, int offX, int offY)
{
	int	my;
	int	mx;

	my = 0;
	while (my < data->y)
	{
		mx = 0;
		while (mx < data->x)
		{
			draw_tile_cell(data, my, mx, scale, offX, offY);
			mx++;
		}
		my++;
	}
}

void	draw_minimap_player(t_data *data, int scale, int offX, int offY)
{
	int	px;
	int	py;
	int	half;
	int	dy;
	int	dx;

	px   = offX + (int)(data->player->x * scale);
	py   = offY + (int)(data->player->y * scale);
	half = 4;
	dy   = -half;
	while (dy <= half)
	{
		dx = -half;
		while (dx <= half)
		{
			put_pixel_to_img(data, px + dx, py + dy, 0xFF0000);
			dx++;
		}
		dy++;
	}
}

void	draw_minimap_on_image(t_data *data)
{
	int	scale;
	int	offX;
	int	offY;

	scale = TILE_MMAP / 2;
	offX  = data->win_width  - data->x * scale;
	offY  = data->win_height - data->y * scale;
	draw_minimap_tiles(data, scale, offX, offY);
	draw_minimap_player(data, scale, offX, offY);
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahaded <abahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:01 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/27 23:17:51 by abahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_images(t_data *data)
{
	if (data->player->textu[0].img)
		mlx_destroy_image(data->mlx, data->player->textu[0].img);
	if (data->player->textu[1].img)
		mlx_destroy_image(data->mlx, data->player->textu[1].img);
	if (data->player->textu[2].img)
		mlx_destroy_image(data->mlx, data->player->textu[2].img);
	if (data->player->textu[3].img)
		mlx_destroy_image(data->mlx, data->player->textu[3].img);
	write(2, "invalid path or invalid image!\n", 31);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	alloc(0, FREE);
	exit(1);
}

void	storing_images(t_data *data)
{
	data->player->textu[0].img = mlx_xpm_file_to_image(data->mlx, data->player->path_NO,
			&data->player->textu[0].width, &data->player->textu[0].height);
	if (!data->player->textu[0].img)
		destroy_images(data);
	data->player->textu[1].img = mlx_xpm_file_to_image(data->mlx, data->player->path_SO,
			&data->player->textu[1].width, &data->player->textu[1].height);
	if (!data->player->textu[1].img)
		destroy_images(data);
	data->player->textu[2].img = mlx_xpm_file_to_image(data->mlx, data->player->path_WE,
			&data->player->textu[2].width, &data->player->textu[2].height);
	if (!data->player->textu[2].img)
		destroy_images(data);
	data->player->textu[3].img = mlx_xpm_file_to_image(data->mlx, data->player->path_EA,
			&data->player->textu[3].width, &data->player->textu[3].height);
	if (!data->player->textu[3].img)
		destroy_images(data);
}

static void locate_player_on_map(t_data *d)
{
    for (int i = 0; i < d->y; i++)
    {
        int row_len = ft_strlen(d->map[i]);
        for (int j = 0; j < row_len; j++)
        {
            char c = d->map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                d->player->x = j + 0.5;
                d->player->y = i + 0.5;
                d->player->dir = c; 
                d->map[i][j] = '0';
                return;
            }
        }
    }
    ft_write_stderr(d, "add just one player!"); 
}

void parsing(t_data *data, char **av)
{
    data->index_checking = 0;
    data->last_line     = 0;

    store_map(data, av);
    store_element(data);
    store_oriandcpy_map(data);

    locate_player_on_map(data);

    checking_map(data);
    storing_images(data);
	data->player->textu[0].addr = mlx_get_data_addr(data->player->textu[0].img,
			&data->player->textu[0].bits_per_pixel, &data->player->textu[0].bits_per_pixel, &data->player->textu[0].endian);
	data->player->textu[1].addr = mlx_get_data_addr(data->player->textu[1].img,
			&data->player->textu[1].bits_per_pixel, &data->player->textu[1].bits_per_pixel, &data->player->textu[1].endian);
	data->player->textu[2].addr = mlx_get_data_addr(data->player->textu[2].img,
			&data->player->textu[2].bits_per_pixel, &data->player->textu[2].bits_per_pixel, &data->player->textu[2].endian);
	data->player->textu[3].addr = mlx_get_data_addr(data->player->textu[3].img,
			&data->player->textu[3].bits_per_pixel, &data->player->textu[3].bits_per_pixel, &data->player->textu[3].endian);
	data->player->textu[0].endian= 1;
}

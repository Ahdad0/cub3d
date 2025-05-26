/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-kher <iel-kher@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:01 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/26 21:06:35 by iel-kher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_images(t_data *data)
{
	if (data->player->NO)
		mlx_destroy_image(data->mlx, data->player->NO);
	if (data->player->SO)
		mlx_destroy_image(data->mlx, data->player->SO);
	if (data->player->WE)
		mlx_destroy_image(data->mlx, data->player->WE);
	if (data->player->EA)
		mlx_destroy_image(data->mlx, data->player->EA);
	write(2, "invalid path or invalid image!\n", 31);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	alloc(0, FREE);
	exit(1);
}

void	storing_images(t_data *data)
{
	int	width;
	int	height;

	data->player->NO = mlx_xpm_file_to_image(data->mlx, data->player->path_NO,
			&width, &height);
	if (!data->player->NO)
		destroy_images(data);
	data->player->SO = mlx_xpm_file_to_image(data->mlx, data->player->path_SO,
			&width, &height);
	if (!data->player->SO)
		destroy_images(data);
	data->player->WE = mlx_xpm_file_to_image(data->mlx, data->player->path_WE,
			&width, &height);
	if (!data->player->WE)
		destroy_images(data);
	data->player->EA = mlx_xpm_file_to_image(data->mlx, data->player->path_EA,
			&width, &height);
	if (!data->player->EA)
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
}

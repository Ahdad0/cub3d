/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-kher <iel-kher@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:01 by abahaded          #+#    #+#             */
/*   Updated: 2025/06/05 20:29:01 by iel-kher         ###   ########.fr       */
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
	data->player->textu = alloc(sizeof(t_texture) * 4, ALLOC);
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

void	set_player_spawn_orientation(t_data *data, char ori)
{
	if (ori == 'N')
	{
		data->player->dir_x   = 0.0;
		data->player->dir_y   = -1.0;
		data->player->plane_x =  0.66;
		data->player->plane_y =  0.0;
	}
	else if (ori == 'S')
	{
		data->player->dir_x   = 0.0;
		data->player->dir_y   =  1.0;
		data->player->plane_x = -0.66;
		data->player->plane_y =  0.0;
	}
	else if (ori == 'E')
	{
		data->player->dir_x   =  1.0;
		data->player->dir_y   =  0.0;
		data->player->plane_x =  0.0;
		data->player->plane_y =  0.66;
	}
	else if (ori == 'W')
	{
		data->player->dir_x   = -1.0;
		data->player->dir_y   =  0.0;
		data->player->plane_x =  0.0;
		data->player->plane_y = -0.66;
	}
}

void	locate_player_on_map(t_data *d)
{
	int	i;
	int	j;
	char	c;

	i = 0;
	while (i < d->y)
	{
		j = 0;
		while (j < (int)ft_strlen(d->map[i]))
		{
			c = d->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				d->player->x = j + 0.5;
				d->player->y = i + 0.5;
				set_player_spawn_orientation(d, c);
				d->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
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
	// load_all_textures(data);
}

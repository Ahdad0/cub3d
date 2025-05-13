/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahaded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:01 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/13 14:56:02 by abahaded         ###   ########.fr       */
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

void	parsing(t_data *data, char **av)
{
	data->index_checking = 0;
	data->last_line = 0;
	store_map(data, av);
	store_element(data);
	check_path_elements(data);
	store_oriandcpy_map(data);
	checking_map(data);
	storing_images(data);
}

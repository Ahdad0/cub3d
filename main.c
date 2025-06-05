/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-kher <iel-kher@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:56 by abahaded          #+#    #+#             */
/*   Updated: 2025/06/05 20:11:21 by iel-kher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	if(data->mlx)
		free(data->mlx);
	exit(0);
	return(0);
}

int	main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		exit(1);
	init_game(&data, av);
	allocate_texture_buffer(&data);
	setup_mlx_loop(&data);
	mlx_loop(data.mlx);
	free_everything(&data);
	return (0);
}

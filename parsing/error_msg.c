/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahaded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:55:39 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/13 14:55:40 by abahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../helper_functions.h"

void	ft_write_stderr(t_data *data, char *string)
{
	int	i;

	i = 0;
	write(2, "Error:\n ", 8);
	while (string[i])
	{
		write(2, &string[i], 1);
		i++;
	}
	write(2, "\n", 1);
	free_everything(data);
	exit(1);
}

void	free_everything(t_data *data)
{
	if (data->player->NO)
		mlx_destroy_image(data->mlx, data->player->NO);
	if (data->player->SO)
		mlx_destroy_image(data->mlx, data->player->SO);
	if (data->player->EA)
		mlx_destroy_image(data->mlx, data->player->EA);
	if (data->player->WE)
		mlx_destroy_image(data->mlx, data->player->WE);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	alloc(0, FREE);
}

// update player->y because y is ++ from 0 not from the map started
// last is when the map start
void	check_path_elements(t_data *data)
{
	if (data->index_checking == 0)
		ft_write_stderr(data, "no type found or the map not found!");
	if (!data->player->path_NO)
		ft_write_stderr(data, "there is a type missing");
	if (!data->player->path_SO)
		ft_write_stderr(data, "there is a type missing");
	if (!data->player->path_WE)
		ft_write_stderr(data, "there is a type missing");
	if (!data->player->path_EA)
		ft_write_stderr(data, "there is a type missing");
	if (!data->player->F_RGB)
		ft_write_stderr(data, "there is a type missing");
	if (!data->player->C_RGB)
		ft_write_stderr(data, "there is a type missing");
	if (data->player->y > data->last_line)
		data->player->y -= data->last_line;
	else
		data->player->y = data->last_line - data->player->y;
}

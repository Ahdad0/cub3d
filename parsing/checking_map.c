/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahaded <abahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:54:24 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/30 00:35:46 by abahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../helper_functions.h"

bool	check_if_true(t_data *data, int i, int y)
{
	if ((!data->cpy_map_parsing[i + 1]
			|| ft_strlen(data->cpy_map_parsing[i + 1]) < (size_t)y)
		|| data->cpy_map_parsing[i + 1][y] == ' '
		|| !data->cpy_map_parsing[i + 1][y]
		|| i == 0
		|| ft_strlen(data->cpy_map_parsing[i - 1]) < (size_t)y
		|| data->cpy_map_parsing[i - 1][y] == ' '
		|| !data->cpy_map_parsing[i - 1][y] || data->cpy_map_parsing[i][y
		+ 1] == ' ' || !data->cpy_map_parsing[i][y + 1]
		|| data->cpy_map_parsing[i][y - 1] == ' ' || y == 0)
		return (true);
	return (false);
}

bool	check_player(t_data *data, int i, int y)
{
	if (data->cpy_map_parsing[i][y] == 'N' || data->cpy_map_parsing[i][y] == 'E'
		|| data->cpy_map_parsing[i][y] == 'W'
		|| data->cpy_map_parsing[i][y] == 'S')
		return (true);
	return (false);
}

bool	check_not_char(t_data *data, int i, int y)
{
	if (data->cpy_map_parsing[i][y] != '1' && data->cpy_map_parsing[i][y] != '0'
		&& data->cpy_map_parsing[i][y] != 'N'
		&& data->cpy_map_parsing[i][y] != ' '
		&& data->cpy_map_parsing[i][y] != 'E'
		&& data->cpy_map_parsing[i][y] != 'W'
		&& data->cpy_map_parsing[i][y] != 'S'
		&& data->cpy_map_parsing[i][y] != 'D')
		return (true);
	return (false);
}

void	helper_checking_map(t_data *data, int i, int *y)
{
	while (data->cpy_map_parsing[i][*y])
	{
		if (check_player(data, i, *y) == true)
			data->index_player++;
		if (data->index_player > 1)
			ft_write_stderr(data, "Error: just one player");
		if (data->cpy_map_parsing[i][*y] == '0')
			if (check_if_true(data, i, *y) == true)
				ft_write_stderr(data, "Not closed");
		if (check_player(data, i, *y) == true)
			if (check_if_true(data, i, *y) == true)
				ft_write_stderr(data, "Not closed");
		if (check_not_char(data, i, *y) == true)
			ft_write_stderr(data, "Unknown character in the map!");
		(*y)++;
	}
}

void	checking_map(t_data *data)
{
	bool	line;
	int		i;
	int		y;

	data->index_player = 0;
	line = false;
	i = 0;
	while (data->cpy_map_parsing[i])
	{
		y = 0;
		if (line == true && ft_strchr(data->cpy_map_parsing[i], '1'))
			ft_write_stderr(data, "it is not the right syntax for the map!");
		if (!ft_strchr(data->cpy_map_parsing[i], '1'))
			line = true;
		helper_checking_map(data, i, &y);
		i++;
	}
	if (data->index_player == 0)
		ft_write_stderr(data, "add just one player!");
}

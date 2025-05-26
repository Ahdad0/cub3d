/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-kher <iel-kher@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:41 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/22 15:54:37 by iel-kher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../helper_functions.h"

void	store_player_position(t_data *data, char *string)
{
	if (ft_strchr(string, 'N') || ft_strchr(string, 'W') || ft_strchr(string,
			'S') || ft_strchr(string, 'E'))
	{
		data->player->x = position_of_char(string, "NWSE");
		data->player->y = data->y;
	}
}

void	coordination_map(t_data *data, char *av)
{
	char	*string;
	int		fd;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		ft_write_stderr(data, "filename fail!");
	string = get_next_line(fd);
	if (string)
	{
		data->x = ft_strlen(string) - 1;
		store_player_position(data, string);
	}
	while (string)
	{
		data->y++;
		free(string);
		string = get_next_line(fd);
		if (!string)
			break ;
		store_player_position(data, string);
	}
	close(fd);
}

void	store_map(t_data *data, char **av)
{
	char	*string;
	int		fd;
	int		o;

	coordination_map(data, av[1]);
	o = 0;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		ft_write_stderr(data, "filename fail!");
	data->cpy_map = alloc((data->y + 1) * sizeof(char *), ALLOC);
	string = get_next_line(fd);
	while (string)
	{
		data->cpy_map[o++] = ft_strdup(string);
		free(string);
		string = get_next_line(fd);
	}
	data->cpy_map[o] = NULL;
}

char	**helper_store_map(t_data *data, int total_lenght, int index, int u)
{
	char	**map;
	int		i;

	i = 0;
	if (u != 0)
		map = alloc((u + 1) * sizeof(char *), ALLOC);
	else
		map = alloc((total_lenght + 1) * sizeof(char *), ALLOC);
	while (data->cpy_map[index])
	{
		if (u != 0 && index == u)
			break ;
		map[i++] = ft_strdup(data->cpy_map[index]);
		if (ft_strchr(map[i - 1], '\n'))
			map[i - 1][ft_strlen(map[i - 1]) - 1] = '\0';
		index++;
	}
	map[index] = NULL;
	return (map);
}

void	store_oriandcpy_map(t_data *data)
{
	// int		index;
	int		u;
	int		cpy_last;
	bool	line;

	line = false;
	// index = 0;
	u = 0;
	cpy_last = data->last_line;
	while (data->cpy_map[cpy_last])
	{
		if (line == false && found_just_char(data->cpy_map[cpy_last], ' ') == 1)
		{
			u = cpy_last;
			line = true;
		}
		cpy_last++;
	}
	data->map = helper_store_map(data, cpy_last, data->last_line, u);
	// int i = 0;
	data->x = 0;
	data->y = 0;
	size_t len = ft_strlen(data->map[0]);
	while (data->map[data->y])
	{
		if (ft_strlen(data->map[data->y]) > len)
			len = ft_strlen(data->map[data->y]);
		data->y++;
	}
	data->x = len;
	data->cpy_map_parsing = helper_store_map(data, cpy_last, data->last_line, u);
}

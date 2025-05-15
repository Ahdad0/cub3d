/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahaded <abahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:41 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/15 16:56:56 by abahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../helper_functions.h"

int	position_of_char(char *string, char *c)
{
	int	i;
	int	y;

	i = 0;
	while (string[i])
	{
		y = 0;
		while (c[y])
		{
			if (c[y] == string[i])
				return (i);
			y++;
		}
		i++;
	}
	return (-1);
}

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

char **helper_store_map(t_data *data, int total_lenght, int index, int u)
{
	char	**map;
	int		i;
	
	// data->map = alloc((tot + 1) * sizeof(char *), ALLOC);
	i = 0;
	if (u != 0)
	{
		map = alloc((u + 1) * sizeof(char *), ALLOC);
	}
	else
		map = alloc((total_lenght + 1) * sizeof(char *), ALLOC);
	while (data->cpy_map[index])
	{
		if (u != 0 && index == u)
			break;
			
		// data->map[index++] = ft_strdup(data->cpy_map[index]);
		map[i++] = ft_strdup(data->cpy_map[index]);
		if (ft_strchr(map[i - 1], '\n'))
			map[i - 1][ft_strlen(map[i - 1])
				- 1] = '\0';
		index++;
	}
	map[index] = NULL;
	// data->cpy_map_parsing[u] = NULL;
	return (map);
}

int	found_just_char(char *map, int c)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] != '\n' && map[i] != c)
			return (0);
		i++;
	}
	return (1);
}
void	store_oriandcpy_map(t_data *data)
{
	int	index;
	int	u;
	int	cpy_last;
	bool	line = false;

	index = 0;
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
	data->cpy_map_parsing = helper_store_map(data, cpy_last, data->last_line, u);
}

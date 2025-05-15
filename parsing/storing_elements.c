/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storing_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahaded <abahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:21 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/15 22:42:51 by abahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../helper_functions.h"

char	**two_arguments(char *one_line)
{
	char	**line;
	int		i;
	char	*new_str;

	i = 0;
	if (ft_strlen(one_line) != 1)
	{
		new_str = ft_strtrim(one_line, "\n\t");
		if (!new_str)
			return (NULL);
	}
	else
		new_str = ft_strdup(one_line);
	line = ft_split(new_str, ' ');
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (ft_strchr(line[i], '\n'))
			line[i][ft_strlen(line[i]) - 1] = '\0';
		i++;
	}
	return (line);
}

void	helperfunc(t_data *data, char **line, int i)
{
	if (len_matrix(line) != 2)
		ft_write_stderr(data, "invalid syntax of type and object!");
	data->last_line = i + 1;
	data->index_checking++;
}

int	store_colors(t_data *data, char **line, int i)
{
	if (ft_strcmp(line[0], "F") == 0)
	{
		helperfunc(data, line, i);
		data->player->F_RGB = split_colors(data, line[1]);
	}
	else if (ft_strcmp(line[0], "C") == 0)
	{
		helperfunc(data, line, i);
		data->player->C_RGB = split_colors(data, line[1]);
	}
	else if (line && line[0] && line[0][0] != '\0')
	{
		if (data->index_checking != 6 && line[0][0] == '1')
			ft_write_stderr(data,
				"false position for the map or not all types found!");
		else if (data->index_checking == 6 && line[0][0] == '1')
		{
			data->last_line = i;
			return (-1);
		}
		ft_write_stderr(data, "unknowed type!");
	}
	return (0);
}

int	store_and_check(t_data *data, char **line, int i)
{
	if (ft_strcmp(line[0], "NO") == 0)
	{
		helperfunc(data, line, i);
		data->player->path_NO = ft_strdup(line[1]);
	}
	else if (ft_strcmp(line[0], "SO") == 0)
	{
		helperfunc(data, line, i);
		data->player->path_SO = ft_strdup(line[1]);
	}
	else if (ft_strcmp(line[0], "WE") == 0)
	{
		helperfunc(data, line, i);
		data->player->path_WE = ft_strdup(line[1]);
	}
	else if (ft_strcmp(line[0], "EA") == 0)
	{
		helperfunc(data, line, i);
		data->player->path_EA = ft_strdup(line[1]);
	}
	else
		return (store_colors(data, line, i));
	return (0);
}

void	store_element(t_data *data)
{
	char	**line;
	int		i;

	i = 0;
	while (data->cpy_map[i])
	{
		line = two_arguments(data->cpy_map[i]);
		if (store_and_check(data, line, i) == -1)
			break ;
		i++;
	}
}

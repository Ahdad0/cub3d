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
	if (ft_strchr(string, 'N') || ft_strchr(string, 'W')
		|| ft_strchr(string, 'S') || ft_strchr(string, 'E'))
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
		ft_write_stderr("filename fail!");
	string = get_next_line(fd);
	if (string)
	{
		data->x = ft_strlen(string) - 1;
		store_player_position(data, string);
	}
	while (string)
	{
		data->y++;
		// free(string);
		string = get_next_line(fd);
		if (!string)
			break;
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
		ft_write_stderr("filename fail!");
	data->cpy_map = malloc((data->y + 1) * sizeof(char *));
	string = get_next_line(fd);
	while (string)
	{
		data->cpy_map[o++] = strdup(string);
		string = get_next_line(fd);
	}
	data->cpy_map[o] = NULL;
}

void	store_oriandcpy_map(t_data *data)
{
	int index;
	int u;
	int cpy_last;

	index = 0;
	u = 0;
	cpy_last = data->last_line;
	while (data->cpy_map[cpy_last])
		cpy_last++;
	data->map = malloc((cpy_last + 1) * sizeof(char *));
	data->cpy_map_parsing = malloc((cpy_last + 1) * sizeof(char *));
	while (data->cpy_map[data->last_line])
	{
		data->map[index++] = ft_strdup(data->cpy_map[data->last_line]);
		data->cpy_map_parsing[u++] = ft_strdup(data->cpy_map[data->last_line]);
		if (ft_strchr(data->cpy_map_parsing[u - 1], '\n'))
			data->cpy_map_parsing[u - 1][ft_strlen(data->cpy_map_parsing[u - 1]) - 1] = '\0';
		data->last_line++;
	}
	data->map[index] = NULL;
	data->cpy_map_parsing[u] = NULL;
}

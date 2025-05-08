#include "../cub3d.h"

int	position_of_char(char *string, char c)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	calculate(t_data *data, char **av)
{
	char	*string;
	int		fd;


	fd = open(av[1], O_RDONLY);
	data->x = 0;
	data->y = 0;
	data->player->x = 0;
	data->player->y = 0;
	string = get_next_line(fd);
	if (string)
	{
		if (ft_strchr(string, 'P'))
		{
			data->player->x = position_of_char(string, 'P');
			data->player->y = 0;
		}
		data->x = ft_strlen(string) - 1;
	}
	while (string)
	{
		data->y++;
		free(string);
		string = get_next_line(fd);
		if (!string)
			break;
		if (ft_strchr(string, 'P'))
		{
			data->player->x = position_of_char(string, 'P');
			data->player->y = data->y;
		}
	}
	close(fd);
	int o = 0;
	fd = open(av[1], O_RDONLY);
	data->cpy_map = malloc((data->y + 1) * sizeof(char *));
	string = get_next_line(fd);
	while (string)
	{
		data->cpy_map[o++] = strdup(string);
		string = get_next_line(fd);
	}
	data->cpy_map[o] = NULL;
}

// int	close_window(int keycode)
// {
// 	(void)keycode;
// 	exit(0);
// }

// int	key_press(int keycode, t_data *data)
// {
// 	if (keycode == 65307)
// 		exit(0);
// 	else if (keycode == 65363)
// 	{
// 		data->player->x += 1;
// 		mlx_put_image_to_window(data->mlx, data->mlx_win,
// 				data->player->player_image, data->player->x * 64, data->player->y * 64);
// 	}
// 	return (0);
// }

// void	draw_line(t_data *data, int y_index, int x_index)
// {
// 	int x = 0;
// 	int y = 0;
// 	int color = 0x00FFFFFF;
// 	while (y < 63)
// 	{
// 		x = 0;
// 		while (x < 63)
// 		{
// 			int offset = (y * data->size_line) + (x * (data->bits / 8));
// 			*(unsigned int *)(data->dataa + offset) = color;
// 			mlx_put_image_to_window(data->mlx, data->mlx_win, data->player->view,
// 				y_index * 64, x_index * 64);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	put_image(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < data->y)
// 	{
// 		j = 0;
// 		while (j < data->x)
// 		{
// 			if (data->cpy_map[i][j] == '1')
// 			{
// 				draw_line(data, j, i);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

char	**two_arguments(char *one_line)
{
	char	**line;
	// bool	found_char;
	// int		i;
	// int		first_index;
	// int		seconde_index;

	// i = 0;
	// found_char = false;
	// first_index = 0;
	// line = malloc(3 * sizeof(char *));
	// while (one_line[i])
	// {
	// 	if (isalpha(one_line[i]) != 0)
	// 	{
	// 		found_char = true;
	// 		seconde_index = i + 1;
	// 	}
	// 	else if (found_char == false && isalpha(one_line[i + 1]) != 0)
	// 		first_index = i + 1;
	// 	i++;
	// }
	line = ft_split(one_line, ' ');
	if (!line)
		return (NULL);
	return (line);
}

void	free_mat(char **arr)
{
	int i = 0;

	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void storing_info(t_data *data)
{
	(void)data;
	char	**line;
	int i = 0;
	int last = 0;

	// two_arguments(data->cpy_map[0]);
	while (data->cpy_map[i])
	{
		line = two_arguments(data->cpy_map[i]);
		if (strcmp(line[0], "NO") == 0)
			data->player->path_NO = strdup(line[1]);
		else if (strcmp(line[0], "SO") == 0)
			data->player->path_SO = strdup(line[1]);
		else if (strcmp(line[0], "WE") == 0)
			data->player->path_WE = strdup(line[1]);
		else if (strcmp(line[0], "EA") == 0)
			data->player->path_EA = strdup(line[1]);
		else if (strcmp(line[0], "F") == 0)
			data->player->color_F = strdup(line[1]);
		else if (strcmp(line[0], "C") == 0)
		{
			data->player->color_C = strdup(line[1]);
			last = i + 2;
		}
		// free_mat(line);
		i++;
	}
	int index = 0;
	int cpy_last = last;
	while (data->cpy_map[cpy_last])
	{
		cpy_last++;
	}
	data->map = malloc((cpy_last + 1) * sizeof(char *));
	while (data->cpy_map[last])
	{
		data->map[index++] = strdup(data->cpy_map[last]);
		last++;
	}
	data->map[index] = NULL;
}

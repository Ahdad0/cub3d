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

char	**two_arguments(char *one_line)
{
	char	**line;
	int i = 0;
	char	*new_str;

	// printf("str=%s, len=%zu\n", one_line, ft_strlen(one_line));
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
		// printf("line:%s\n", line[i]);
		i++;
	}
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

void	destroy_images(t_data *data)
{
	printf("invalid path or invalid image!\n");
	if (data->player->NO)
		mlx_destroy_image(data->mlx, data->player->NO);
	if (data->player->SO)
		mlx_destroy_image(data->mlx, data->player->SO);
	if (data->player->WE)
		mlx_destroy_image(data->mlx, data->player->WE);
	if (data->player->EA)
		mlx_destroy_image(data->mlx, data->player->EA);
	exit(1);
}

void	storing_images(t_data *data)
{
	int width;
	int height;
	
	data->player->NO = NULL;
	data->player->SO = NULL;
	data->player->WE = NULL;
	data->player->EA = NULL;

	// data->player->path_NO[strlen(data->player->path_NO) - 1] = '\0';
	data->player->NO = mlx_xpm_file_to_image(data->mlx, data->player->path_NO, &width, &height);
	if (!data->player->NO)
		destroy_images(data);

	// data->player->path_SO[strlen(data->player->path_SO) - 1] = '\0';
	data->player->SO = mlx_xpm_file_to_image(data->mlx, data->player->path_SO, &width, &height);
	if (!data->player->SO)
		destroy_images(data);

	// data->player->path_WE[strlen(data->player->path_WE) - 1] = '\0';
	data->player->WE = mlx_xpm_file_to_image(data->mlx, data->player->path_WE, &width, &height);
	if (!data->player->WE)
		destroy_images(data);

	// data->player->path_EA[strlen(data->player->path_EA) - 1] = '\0';
	data->player->EA = mlx_xpm_file_to_image(data->mlx, data->player->path_EA, &width, &height);
	if (!data->player->EA)
		destroy_images(data);
}

int	len_matrix(char **array)
{
	int i = 0;

	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

void	checking_color(char *line)
{
	char **l;

	l = ft_split(line, ',');
	if (!l)
		return ;
	if (len_matrix(l) != 3)
	{
		printf("");
	}
}

int	cout_char(char *str, char c)
{
	int i = 0;
	int index = 0;

	while (str[i])
	{
		if (str[i] == c)
			index++;
		i++;
	}
	return (index);
}
int	*split_colors(char *line)
{
	char **new;
	int	*color;
	int	num;

	num = 0;
	new = ft_split(line, ',');
	if (!new)
		return (NULL);
	if (len_matrix(new) != 3 || cout_char(line, ',') != 2)
	{
		printf("Error in the RGB!\n");
		exit(1);
	}
	color = malloc(3 * sizeof(int));
	if (!color)
		return (NULL);
	num = ft_atoi(new[0]);
	if (num > 255 || num < 0)
	{
		printf("this number is not acceptable in RGB!\n");
		exit(1);
	}
	color[0] = ft_atoi(new[0]);
	num = ft_atoi(new[1]);
	if (num > 255 || num < 0)
	{
		printf("this number is not acceptable in RGB!\n");
		exit(1);
	}
	color[1] = ft_atoi(new[1]);
	num = ft_atoi(new[2]);
	if (num > 255 || num < 0)
	{
		printf("this number is not acceptable in RGB!\n");
		exit(1);
	}
	color[2] = ft_atoi(new[2]);
	return (color);
}

void	checking_map(t_data *data)
{
	int i = 0;
	int y = 0;
	// bool line = false;

	while (data->cpy_map_parsing[i])
	{
		y = 0;
		// if (line == true && ft_strchr(data->cpy_map_parsing[i], '1'))
		// {
		// 	printf("it is not the right syntax for the map!\n");
		// 	exit(1);
		// }
		// if (!ft_strchr(data->cpy_map_parsing[i], '1'))
		// {
		// 	printf("line found = %s\n", data->cpy_map_parsing[i]);
		// 	line = true;
		// }
		while (data->cpy_map_parsing[i][y])
		{
			if (data->cpy_map_parsing[i][y] == '0')
			{
				if ((!data->cpy_map_parsing[i + 1] || ft_strlen(data->cpy_map_parsing[i + 1]) < (size_t)y)
				|| data->cpy_map_parsing[i + 1][y] == ' ' || !data->cpy_map_parsing[i + 1][y]
				|| data->cpy_map_parsing[i - 1][y] == ' ' || ft_strlen(data->cpy_map_parsing[i - 1]) < (size_t)y
				|| !data->cpy_map_parsing[i - 1][y] || data->cpy_map_parsing[i][y + 1] == ' '
				|| !data->cpy_map_parsing[i][y + 1] || data->cpy_map_parsing[i][y - 1] == ' '
				|| y == 0)
				{
					printf("Not closed\n");
					// printf("len_matrix=%d, and i = %d\n", len_matrix(data->cpy_map_parsing), i);
					// printf("up=%c, down=%c, right=%c, left=%c\n", data->cpy_map_parsing[i + 1][y],
					// 	data->cpy_map_parsing[i - 1][y], data->cpy_map_parsing[i][y + 1],
					// 	data->cpy_map_parsing[i][y - 1]);
					// printf("the char is %c in i=%d, y=%d\n", data->cpy_map_parsing[i][y], i, y);
					// printf("len = %zu, i = %d\n", ft_strlen(data->cpy_map_parsing[i + 1]), i);
					exit(1);
				}
			}
			y++;
		}
		i++;
	}
}

void	parsing(t_data *data, char **av)
{
	(void)data;
	char	**line;
	int i = 0;
	int last = 0;
	int index = 0;
	
	calculate(data, av);

	data->player->path_NO = NULL;
	data->player->path_SO = NULL;
	data->player->path_WE = NULL;
	data->player->path_EA = NULL;
	data->player->C_RGB = NULL;
	data->player->F_RGB = NULL;

	while (data->cpy_map[i])
	{
		line = two_arguments(data->cpy_map[i]);
		if (ft_strcmp(line[0], "NO") == 0)
		{
			if (len_matrix(line) != 2)
			{
				printf("invalid syntax of type and object!\n");
				exit(1);
			}
			data->player->path_NO = strdup(line[1]);
			last = i + 1;
			index++;
		}
		else if (ft_strcmp(line[0], "SO") == 0)
		{
			if (len_matrix(line) != 2)
			{
				printf("invalid syntax of type and object!\n");
				exit(1);
			}
			data->player->path_SO = strdup(line[1]);
			last = i + 1;
			index++;
		}
		else if (ft_strcmp(line[0], "WE") == 0)
		{
			if (len_matrix(line) != 2)
			{
				printf("invalid syntax of type and object!\n");
				exit(1);
			}
			data->player->path_WE = strdup(line[1]);
			last = i + 1;
			index++;
		}
		else if (ft_strcmp(line[0], "EA") == 0)
		{
			if (len_matrix(line) != 2)
			{
				printf("invalid syntax of type and object!\n");
				exit(1);
			}
			data->player->path_EA = strdup(line[1]);
			last = i + 1;
			index++;
		}
		else if (ft_strcmp(line[0], "F") == 0)
		{
			if (len_matrix(line) != 2)
			{
				printf("invalid syntax of type and object!\n");
				exit(1);
			}
			// checking_color(line[1]);
			data->player->F_RGB = split_colors(line[1]);
			last = i + 1;
			index++;
		}
		else if (ft_strcmp(line[0], "C") == 0)
		{
			if (len_matrix(line) != 2)
			{
				printf("invalid syntax of type and object!\n");
				exit(1);
			}
			data->player->C_RGB = split_colors(line[1]);
			last = i + 1;
			index++;
		}
		else if (line && line[0] && line[0][0] != '\0')
		{
			if (index != 6 && (line[0][0] == '1' || line[0][0] == '0'))
			{
				printf("false position for the map or not all types found!\n");
				exit(1);
			}
			// printf("line=%s\n", line[0]);
			printf("unknowed type!\n");
			exit(1);
		}
		if (index == 6)
		{
			// printf("found all the types\n");
			break;
		}
		// free_mat(line);
		i++;
	}

	// fix i + 2 between last type and the map
	if (index == 0)
	{
		printf("no type found or the map not found!\n");
		exit(1);
	}
	if (!data->player->path_NO)
	{
		printf("there is a type missing\n");
		exit(1);
	}
	if (!data->player->path_SO)
	{
		printf("there is a type missing!\n");
		exit(1);
	}
	if (!data->player->path_WE)
	{
		printf("there is a type missing!\n");
		exit(1);
	}
	if (!data->player->path_EA)
	{
		printf("there is a type missing!\n");
		exit(1);
	}
	if (!data->player->F_RGB)
	{
		printf("there is type missing\n");
		exit(1);
	}
	if (!data->player->C_RGB)
	{
		printf("there is type missing\n");
		exit(1);
	}
	index = 0;
	int u = 0;
	int cpy_last = last;
	while (data->cpy_map[cpy_last])
	{
		cpy_last++;
	}
	data->map = malloc((cpy_last + 1) * sizeof(char *));
	data->cpy_map_parsing = malloc((cpy_last + 1) * sizeof(char *));
	while (data->cpy_map[last])
	{
		data->map[index++] = ft_strdup(data->cpy_map[last]);
		data->cpy_map_parsing[u++] = ft_strdup(data->cpy_map[last]);
		if (ft_strchr(data->cpy_map_parsing[u - 1], '\n'))
			data->cpy_map_parsing[u - 1][ft_strlen(data->cpy_map_parsing[u - 1]) - 1] = '\0';
		last++;
	}
	data->map[index] = NULL;
	data->cpy_map_parsing[u] = NULL;
	// i = 0;
	// while (data->cpy_map_parsing[i])
	// {
	// 	printf("%s\n", data->cpy_map_parsing[i]);
	// 	i++;
	// }
	checking_map(data);
	storing_images(data);
}

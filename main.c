#include "test.h"

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
	data->map = malloc((data->y + 1) * sizeof(char *));
	string = get_next_line(fd);
	while (string)
	{
		data->map[o++] = strdup(string);
		string = get_next_line(fd);
	}
	data->map[o] = NULL;
}

int	close_window(int keycode)
{
	(void)keycode;
	exit(0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == 65363)
	{
		data->player->x += 1;
		mlx_put_image_to_window(data->mlx, data->mlx_win,
				data->player->player_image, data->player->x * 64, data->player->y * 64);
	}
	return (0);
}

void	draw_line(t_data *data, int y_index, int x_index)
{
	int x = 0;
	int y = 0;
	int color = 0x00FFFFFF;
	while (y < 63)
	{
		x = 0;
		while (x < 63)
		{
			int offset = (y * data->size_line) + (x * (data->bits / 8));
			*(unsigned int *)(data->dataa + offset) = color;
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->player->view,
				y_index * 64, x_index * 64);
			x++;
		}
		y++;
	}
}

void	put_image(t_data *data)
{
	int	i;
	int	j;4

	i = 0;
	while (i < data->y)
	{
		j = 0;
		while (j < data->x)
		{
			if (data->map[i][j] == '1')
			{
				draw_line(data, j, i);
			}
			j++;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	t_data *data;
	t_player player;
	// int		height;
	// int		wight;

	(void)ac;
	data = malloc(sizeof(t_data));
	data->player = &player;
	data->mlx = mlx_init();
	calculate(data, av);
	data->mlx_win = mlx_new_window(data->mlx, data->x * 64, data->y * 64, "New");
	// printf("data=%s-\n", dataa);
	data->player->view = mlx_new_image(data->mlx, 63, 63);
	data->dataa = mlx_get_data_addr(data->player->view, &data->bits, &data->size_line, &data->endian);
	put_image(data);
	// mlx_put_image_to_window(data->mlx, data->mlx_win,
	// 			data->player->player_image, data->player->x * 64, data->player->y * 64);
	mlx_hook(data->mlx_win, 2, 17, key_press, data);
	mlx_hook(data->mlx_win, 17, 1L<<17, close_window, NULL);
	mlx_loop(data->mlx);
}
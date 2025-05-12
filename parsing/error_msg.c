#include "../helper_functions.h"

void	ft_write_stderr(char *string)
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
	exit(1);
}

// update player->y because y is ++ from 0 not from the map started
// last is when the map start
void	check_path_elements(t_data *data)
{
	if (data->index_checking == 0)
		ft_write_stderr("no type found or the map not found!");
	if (!data->player->path_NO)
		ft_write_stderr("there is a type missing");
	if (!data->player->path_SO)
		ft_write_stderr("there is a type missing");
	if (!data->player->path_WE)
		ft_write_stderr("there is a type missing");
	if (!data->player->path_EA)
		ft_write_stderr("there is a type missing");
	if (!data->player->F_RGB)
		ft_write_stderr("there is a type missing");
	if (!data->player->C_RGB)
		ft_write_stderr("there is a type missing");
	if (data->player->y > data->last_line)
		data->player->y -= data->last_line;
	else
		data->player->y = data->last_line - data->player->y;
}

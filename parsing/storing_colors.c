#include "../helper_functions.h"

void	helper_split_colors(int *color, char **new)
{
	int	num;

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
}

int	*split_colors(char *line)
{
	char	**new;
	int		*color;
	int		num;

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
	helper_split_colors(color, new);
	return (color);
}
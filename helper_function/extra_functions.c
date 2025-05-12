#include "../helper_functions.h"

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

int	len_matrix(char **array)
{
	int i = 0;

	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
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


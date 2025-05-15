/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahaded <abahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:51:34 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/15 19:15:45 by abahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../helper_functions.h"

void	free_mat(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	len_matrix(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

int	cout_char(char *str, char c)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (str[i])
	{
		if (str[i] == c)
			index++;
		i++;
	}
	return (index);
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

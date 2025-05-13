/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahaded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:10 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/13 14:56:11 by abahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../helper_functions.h"

void	helper_split_colors(t_data *data, int *color, char **new)
{
	int	num;

	num = ft_atoi(new[0]);
	if (num > 255 || num < 0)
		ft_write_stderr(data, "this number is not acceptable in RGB!");
	color[0] = ft_atoi(new[0]);
	num = ft_atoi(new[1]);
	if (num > 255 || num < 0)
		ft_write_stderr(data, "this number is not acceptable in RGB!");
	color[1] = ft_atoi(new[1]);
	num = ft_atoi(new[2]);
	if (num > 255 || num < 0)
		ft_write_stderr(data, "this number is not acceptable in RGB!");
	color[2] = ft_atoi(new[2]);
}

int	found_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(line[i] >= '0' && line[i] <= '9') && line[i] != ',')
		{
			if (line[i] == '+' && line[i - 1] == ',' && (line[i + 1] >= '0'
					&& line[i + 1] <= '9'))
				break ;
			return (true);
		}
		i++;
	}
	return (false);
}

int	*split_colors(t_data *data, char *line)
{
	char	**new;
	int		*color;
	int		num;

	num = 0;
	new = ft_split(line, ',');
	if (!new)
		return (NULL);
	if (found_char(line) == true || len_matrix(new) != 3 || cout_char(line,
			',') != 2)
		ft_write_stderr(data, "Error in the RGB!");
	color = alloc(3 * sizeof(int), ALLOC);
	if (!color)
		return (NULL);
	helper_split_colors(data, color, new);
	return (color);
}

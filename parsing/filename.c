/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahaded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:55:47 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/13 14:55:49 by abahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../helper_functions.h"

bool	checking_filename_nobackslach(char **av)
{
	char	*check_filename;
	bool	valid;

	valid = false;
	check_filename = ft_strchr(av[1], '.');
	if (check_filename)
	{
		check_filename++;
		if (*check_filename == 'c')
		{
			check_filename++;
			if (*check_filename == 'u')
			{
				check_filename++;
				if (*check_filename == 'b')
				{
					check_filename++;
					if (!(*check_filename))
						valid = true;
				}
			}
		}
	}
	return (valid);
}

void	checking_filename_backslach(char **av)
{
	char	*check_filename;

	check_filename = ft_strchr(av[1], '/');
	if (check_filename)
	{
		check_filename++;
		if (*check_filename == '.')
		{
			write(2, "Error:\n the filename need to be ex: map.cub\n", 44);
			exit(1);
		}
	}
	else if (av[1][0] == '.')
	{
		write(2, "Error:\n in the filename!\n", 25);
		exit(1);
	}
}

void	checking_filename(char **av)
{
	checking_filename_backslach(av);
	if (checking_filename_nobackslach(av) == false)
	{
		write(2, "Error:\n in the filename!\n", 25);
		exit(1);
	}
}

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
			ft_write_stderr("the filename need to be ex: map.cub");
	}
	else
		if (av[1][0] == '.')
			ft_write_stderr("in the filename!");
}

void	checking_filename(char **av)
{
	checking_filename_backslach(av);
	if (checking_filename_nobackslach(av) == false)
		ft_write_stderr("in the filename!");
}

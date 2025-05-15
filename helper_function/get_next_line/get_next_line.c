/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahaded <abahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:10:49 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/15 19:05:41 by abahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *store)
{
	char	*b;
	char	*new_temp;
	int		i;

	if (!store)
		store = ft_strduup("");
	b = malloc(BUFFER_SIZE + 1);
	if (!b)
		return (free(store), NULL);
	while (ft_strchr(store, '\n') == NULL)
	{
		i = read(fd, b, BUFFER_SIZE);
		if (i == -1)
			return (free(b), free(store), NULL);
		if (i == 0)
			break ;
		b[i] = '\0';
		new_temp = ft_strjoin(store, b);
		free(store);
		if (!new_temp)
			return (free(b), NULL);
		store = new_temp;
	}
	free(b);
	return (store);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*re;
	static char	*store;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	store = read_line(fd, store);
	if (!store)
		return (NULL);
	if (!*store)
		return (free(store), store = NULL, NULL);
	re = ft_untilnewline(store);
	if (!re)
		return (free(store), store = NULL, NULL);
	line = ft_afternewline(store);
	free(store);
	store = line;
	return (re);
}

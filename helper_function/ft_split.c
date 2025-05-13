/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahaded <abahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:51:57 by abahaded          #+#    #+#             */
/*   Updated: 2025/05/13 14:53:38 by abahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../helper_functions.h"

static int	count(char const *s, char c)
{
	int	i;
	int	cou;

	i = 0;
	cou = 0;
	while (s[i])
	{
		if (((s[i] != c && s[i] != '\t') && (s[i + 1] == c || s[i + 1] == '\t'))
			|| ((s[i] != c && s[i] != '\t') && s[i + 1] == '\0'))
			cou++;
		i++;
	}
	return (cou);
}

static int	ft_l(char *s, char c, int *j)
{
	int	len;

	len = 0;
	while (s[*j])
	{
		if (s[*j] != c && s[*j] != '\t')
			len++;
		else if (len != 0 && (s[*j] == c || s[*j] != c))
			break ;
		(*j)++;
	}
	return (len);
}

static char	*ft_str(char *s, char c, int *j)
{
	char	*p;
	int		i;
	int		o;
	int		len;
	int		ll;

	o = 0;
	i = *j;
	while (s[i] == c || s[i] == '\t')
		i++;
	ll = ft_l(s, c, j);
	p = alloc(ll + 1, ALLOC);
	if (!p)
		return (NULL);
	len = *j;
	while (i < len)
		p[o++] = s[i++];
	p[o] = '\0';
	return (p);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		num;
	int		j;
	char	**n;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	num = count(s, c);
	n = alloc((num + 1) * (sizeof(char *)), ALLOC);
	if (!n)
	{
		free(n);
		return (NULL);
	}
	while (num--)
		n[i++] = ft_str((char *)s, c, &j);
	n[i] = NULL;
	return (n);
}

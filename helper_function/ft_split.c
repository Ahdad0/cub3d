#include "../helper_functions.h"

static int	count(char const *s, char c)
{
	int	i;
	int	cou;

	i = 0;
	cou = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			cou++;
		i++;
	}
	return (cou);
}

void	free_p(char **s, unsigned int o)
{
	unsigned int	i;

	i = 0;
	while (i <= o)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static int	ft_l(char *s, char c, int *j)
{
	int	len;

	len = 0;
	while (s[*j])
	{
		if (s[*j] != c)
			len++;
		else if (len != 0 && s[*j] == c)
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
	while (s[i] == c)
		i++;
	ll = ft_l(s, c, j);
	p = malloc(ll + 1);
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
	n = malloc((num + 1) * (sizeof(char *)));
	if (!n)
	{
		free(n);
		return (NULL);
	}
	while (num--)
	{
		n[i++] = ft_str((char *)s, c, &j);
		if (!n[i - 1])
		{
			free_p(n, i - 1);
			return (NULL);
		}
	}
	n[i] = NULL;
	return (n);
}
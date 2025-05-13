#include "../helper_functions.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*p;
	int		i;

	len = ft_strlen(s);
	i = 0;
	p = alloc(len + 1, ALLOC);
	if (!p)
		return (NULL);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

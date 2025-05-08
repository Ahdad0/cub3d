#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
void	free_p(char **s, unsigned int o);

#endif
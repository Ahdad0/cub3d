#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum {
    ALLOC,
    FREE
} e_action;

typedef struct s_garbage{
    void *ptr;
    struct s_garbage *next;
}   t_garbage;

char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
void	free_p(char **s, unsigned int o);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int    ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s);
int	ft_atoi(const char *nptr);
void *alloc(size_t size, t_garbage *garbage, e_action action);
#endif
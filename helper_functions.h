#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "cub3d.h"

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
void *alloc(size_t size, e_action action);
void	free_mat(char **arr);
int	len_matrix(char **array);
int	cout_char(char *str, char c);
int	position_of_char(char *string, char *c);
int	found_just_char(char *map, int c);

#endif
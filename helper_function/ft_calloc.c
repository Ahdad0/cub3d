#include "../helper_functions.h"

void *ft_calloc(size_t count, size_t size)
{
    void *ptr;
    size_t total;

    total = count * size;
    ptr = malloc(total);
    if (!ptr)
        return (NULL);
    memset(ptr, 0, total);
    return (ptr);
}

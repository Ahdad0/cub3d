#include "../helper_functions.h"

void	free_garbage(t_garbage **garbage)
{
	t_garbage	*temp;

	if (!garbage)
		return ;
	if (*garbage)
	{
		while (*garbage)
		{
			temp = *garbage;
			*garbage = (*garbage)->next;
			if (temp->ptr)
				free(temp->ptr);
			free(temp);
		}
	}
}

t_garbage *new_garbage(void *allocated)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return (write(2,"malloc failure\n",15) ,NULL);
	new->ptr = allocated;
	new->next = NULL;
	return (new);
}

void	garbage_add_back(void *allocated, t_garbage **garbage)
{
	t_garbage	*last;
    t_garbage *new_allocation;

	if (!garbage)
		return ;
    new_allocation = new_garbage(allocated);
    if (!new_allocation)
        return (free(allocated));
    if (!*garbage)
	{
		*garbage = new_allocation;
		return ;
	}
	last = *garbage;
	while (last->next)
		last = last->next;
	if (last)
		last->next = new_allocation;
}

void *alloc(size_t size, e_action action)
{
    void *returned;
	static t_garbage *garbage;
	
    if(action == ALLOC)
    {
        returned = malloc(size);
        if (!returned)
            return (write(2,"malloc failure\n",15) ,NULL);
        garbage_add_back(returned, &garbage);
        return (returned);
    }
    else if (action == FREE)
        free_garbage(&garbage);
    return (NULL);
}

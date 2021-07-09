#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*elem;

	if (!lst)
		return (0);
	elem = lst;
	size = 0;
	while (elem)
	{
		elem = elem->next;
		size++;
	}
	return (size);
}

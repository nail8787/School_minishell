#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list *elem;

	if (!lst)
		return (NULL);
	elem = lst;
	while (elem->next)
		elem = elem->next;
	return (elem);
}

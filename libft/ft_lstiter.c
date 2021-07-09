#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *elem;

	if (!lst || !f)
		return ;
	elem = lst;
	while (elem)
	{
		f(elem->content);
		elem = elem->next;
	}
}

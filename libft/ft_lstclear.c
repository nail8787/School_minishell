#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *elem;
	t_list *tmp;

	if (!(*lst))
		return ;
	elem = *lst;
	while (elem)
	{
		tmp = elem;
		elem = elem->next;
		ft_lstdelone(tmp, del);
	}
	*lst = NULL;
}

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *elem;

	if (new && lst)
	{
		if (*lst)
		{
			elem = *lst;
			while (elem->next)
				elem = elem->next;
			elem->next = new;
		}
		else
			*lst = new;
	}
}

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*sym;

	sym = (char *)s;
	i = 0;
	while (i < n)
	{
		sym[i] = c;
		i++;
	}
	return (s);
}

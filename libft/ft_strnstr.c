#include <stdlib.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t i;
	size_t j;
	size_t llen;

	llen = ft_strlen(little);
	if (llen == 0)
		return ((char*)big);
	i = 0;
	while (i < n && big[i] != 0)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < n)
		{
			if (j == llen - 1)
				return ((char*)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

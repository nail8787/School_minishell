#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	size;

	size = ft_strlen(s) + 1;
	new = (char*)malloc(size);
	if (new)
		ft_strlcpy(new, s, size);
	return (new);
}

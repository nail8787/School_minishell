#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int len;

	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[len - i] == c)
			return ((char*)s + len - i);
		i++;
	}
	return (0);
}

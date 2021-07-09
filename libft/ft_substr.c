#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	lens;
	size_t	lenn;
	char	*sub;

	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	if (lens - 1 < (size_t)start)
		return (ft_strdup(""));
	if (start + len > lens)
		lenn = lens - start;
	else
		lenn = len;
	if (!(sub = (char*)malloc(lenn + 1)))
		return (NULL);
	ft_memcpy(sub, s + start, lenn);
	sub[lenn] = 0;
	return (sub);
}

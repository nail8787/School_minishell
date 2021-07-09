#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t dlen;
	size_t slen;

	dlen = 0;
	slen = ft_strlen(src);
	while (dlen < size && dest[dlen] != 0)
		dlen++;
	if (size > dlen)
	{
		ft_strlcpy(dest + dlen, src, size - dlen);
		return (dlen + slen);
	}
	else
		return (size + slen);
}

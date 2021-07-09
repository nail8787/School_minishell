#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	char	*s_end;
	size_t	s_len;

	if (!src)
		return (0);
	s_len = ft_strlen(src);
	if (size > 0 && dest)
	{
		s_end = ft_memccpy(dest, src, 0, size - 1);
		if (s_end)
			*(s_end - 1) = 0;
		else
			dest[size - 1] = 0;
	}
	return (s_len);
}

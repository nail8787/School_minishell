#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (src > dst)
			((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
		else
			((unsigned char*)dst)[n - i - 1] = ((unsigned char*)src)[n - i - 1];
		i++;
	}
	return (dst);
}

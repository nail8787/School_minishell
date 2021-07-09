#include "libft.h"

static int	in_set(char c, const char *set)
{
	size_t i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	lens;
	size_t	end;
	size_t	start;

	if (!s1)
		return (NULL);
	lens = ft_strlen(s1);
	start = 0;
	while (start < lens && in_set(s1[start], set))
		start++;
	end = 0;
	while (end < lens - start && in_set(s1[lens - end - 1], set))
		end++;
	if (!(new = (char*)malloc(lens - start - end + 1)))
		return (NULL);
	ft_memcpy(new, s1 + start, lens - start - end);
	new[lens - start - end] = 0;
	return (new);
}

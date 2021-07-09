#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len;
	char			*new;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (!(new = (char*)malloc(len + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[len] = 0;
	return (new);
}

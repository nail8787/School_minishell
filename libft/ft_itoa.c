#include "libft.h"

static int	nb_len(int nb)
{
	long	n;
	int		len;

	n = nb;
	len = 0;
	if (nb <= 0)
	{
		len++;
		n *= -1;
	}
	while (n >= 1)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		len;
	int		fin;

	len = nb_len(n);
	nb = n;
	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len] = 0;
	fin = 0;
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
		fin = 1;
	}
	while (--len >= fin)
	{
		str[len] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}

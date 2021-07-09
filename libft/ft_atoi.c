
int	ft_atoi(const char *str)
{
	int res;
	int positive;

	positive = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		positive = -1;
	}
	while ((*str >= 48 && *str <= 57) && *str != 0)
	{
		res = 10 * res + (*str - 48);
		str++;
	}
	return (res * positive);
}

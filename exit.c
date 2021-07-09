#include "minishell.h"

static int	error_numeric(t_shell *shell)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(shell->command.args[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	return (255);
}

static int	check_overflow(unsigned long long res, int sign, t_shell *shell)
{
	if (sign == -1 && ft_strcmp(shell->command.args[1],
			"-9223372036854775808") == 0)
		return (res * sign);
	else
		return (error_numeric(shell));
}

long long	ft_atoi_exit(const char *str, t_shell *shell)
{
	unsigned long long	res;
	int					positive;

	positive = 1;
	res = 0;
	if (ft_strlen(str) > 20)
		return (error_numeric(shell));
	while ((*str >= 9 && *str <= 13) || *str == ' ')
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
	if (res > 9223372036854775807)
		return (check_overflow(res, positive, shell));
	write(1, "exit\n", 5);
	return (res * positive);
}

void		normal_exit(t_shell *shell)
{
	int	i;

	free(shell->home);
	write(1, "exit\n", 5);
	i = check_if_key_exists("?", shell->env);
	exit(ft_atoi(&shell->env[i][2]));
}

void		ft_exit(t_shell *shell)
{
	int i;

	i = 0;
	if (shell->command.args[1])
	{
		while (shell->command.args[1][i])
		{
			if (i == 0 && (shell->command.args[1][i] == '-' ||
					shell->command.args[1][i] == '+'))
				i++;
			else if (ft_isdigit(shell->command.args[1][i]) == 1)
				i++;
			else
				exit(error_numeric(shell));
		}
		if (shell->command.args[1] && shell->command.args[2])
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			errno = -1;
			return ;
		}
		exit(ft_atoi_exit(shell->command.args[1], shell));
	}
	else
		normal_exit(shell);
}

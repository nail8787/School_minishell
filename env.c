#include "minishell.h"

int		check_if_value_exists(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		else
			str++;
	}
	return (0);
}

void	ft_env(char **env_copy)
{
	while (*env_copy)
	{
		if (check_if_value_exists(*env_copy) == 0)
			env_copy++;
		else
		{
			if (**env_copy == '?')
			{
				env_copy++;
				continue ;
			}
			ft_putstr_fd(*env_copy, 1);
			ft_putchar_fd('\n', 1);
			env_copy++;
		}
	}
}

#include "minishell.h"

int		ft_echo(t_shell *shell)
{
	int	i;

	i = 1;
	if (shell->command.args[i])
	{
		if (ft_strcmp(shell->command.args[i], "-n") == 0)
			while (ft_strcmp(shell->command.args[i], "-n") == 0)
				i++;
		while (shell->command.args[i])
		{
			ft_putstr_fd(shell->command.args[i++], 1);
			if (shell->command.args[i])
				ft_putchar_fd(' ', 1);
		}
		if (ft_strncmp(shell->command.args[1], "-n", 2) != 0)
			ft_putchar_fd('\n', 1);
	}
	else
		ft_putchar_fd('\n', 1);
	return (0);
}

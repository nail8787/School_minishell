#include "minishell.h"

static int	change_errno(int num)
{
	errno = num;
	return (0);
}

static void	if_export(t_shell *shell)
{
	int i;

	i = 1;
	if (!shell->command.args[i])
		ft_export(NULL, shell);
	else
		while (shell->command.args[i])
			ft_export(shell->command.args[i++], shell);
}

static int	if_binary(t_shell *shell)
{
	struct stat	stats;
	int			status;

	if (check_in_path(shell) != -2)
		return (0);
	if (ft_strchr(shell->command.args[0], '/'))
	{
		if (stat(shell->command.args[0], &stats) != 0)
			return (change_errno(125));
		else
		{
			if (!(stats.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
				return (change_errno(126));
		}
		status = start_binary(shell->command.args[0],
				shell->command.args, shell->env);
		change_question(status, shell);
		errno = -2;
		return (0);
	}
	return (change_errno(127));
}

int			choose_cmd(t_shell *shell)
{
	int		i;

	i = 1;
	errno = 0;
	if (ft_strcmp(shell->command.args[0], "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(shell->command.args[0], "cd") == 0)
		ft_cd(shell->command.args[1], shell);
	else if (ft_strcmp(shell->command.args[0], "export") == 0)
		if_export(shell);
	else if (ft_strcmp(shell->command.args[0], "unset") == 0)
		while (shell->command.args[i])
			ft_unset(shell->command.args[i++], shell);
	else if (ft_strcmp(shell->command.args[0], "env") == 0)
		ft_env(shell->env);
	else if (ft_strcmp(shell->command.args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(shell->command.args[0], "exit") == 0)
		ft_exit(shell);
	else
		if_binary(shell);
	error_check(shell);
	errno = 0;
	return (1);
}

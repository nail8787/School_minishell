#include "minishell.h"

void	print_errors(char *str, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(shell->command.args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
}

void	error_check(t_shell *shell)
{
	if (errno == -1)
		change_question(1, shell);
	else if (errno == 127)
		cmd_not_found(shell);
	else if (errno > 0 && errno <= 102)
		std_errno(shell);
	else if (errno == 125)
		binary_not_found(shell);
	else if (errno == 126)
		perm_denied(shell);
	else if (errno == 128)
		error_not_oldpwd(shell);
	else if (errno == 129)
		error_not_valid_iden(shell);
	else if (errno == 130)
		change_question(errno, shell);
	else if (errno == 131)
		change_question(errno, shell);
	else if (errno == -2)
		return ;
	else
		change_question(0, shell);
}

int		error_not_oldpwd(t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(shell->command.args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("OLDPWD not set", 2);
	change_question(1, shell);
	return (1);
}

int		error_not_valid_iden(t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(shell->command.args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(shell->error.err_iden, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("not a valid identifier", 2);
	change_question(1, shell);
	free(shell->error.err_iden);
	shell->error.err_iden = NULL;
	return (1);
}

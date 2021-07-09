#include "minishell.h"

void	std_errno(t_shell *shell)
{
	change_question(1, shell);
	print_errors(strerror(errno), shell);
}

void	cmd_not_found(t_shell *shell)
{
	change_question(errno, shell);
	print_errors("command not found", shell);
}

void	binary_not_found(t_shell *shell)
{
	change_question(127, shell);
	print_errors(strerror(2), shell);
}

void	perm_denied(t_shell *shell)
{
	change_question(126, shell);
	print_errors(strerror(13), shell);
}

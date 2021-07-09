#include "minishell.h"

void	change_question(int exit_status, t_shell *shell)
{
	char *tmp;
	char *tmp_status;

	if (!(tmp_status = ft_itoa(exit_status)))
		memory_alloc_error();
	if (!(tmp = ft_strjoin("?=", tmp_status)))
		memory_alloc_error();
	shell->env = export_add_key(tmp, shell->env);
	free(tmp_status);
	free(tmp);
}

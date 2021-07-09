#include "minishell.h"

void	print_syntax_error(int error, t_shell *shell)
{
	if (error >= 12 && error <= 16)
		ft_putstr_fd("minishell: ", 1);
	if (error == 12)
		ft_putendl_fd("syntax error near unexpected token `>'", 1);
	else if (error == 13)
		ft_putendl_fd("syntax error near unexpected token `<'", 1);
	else if (error == 14)
		ft_putendl_fd("syntax error near unexpected token `|'", 1);
	else if (error == 15)
		ft_putendl_fd("syntax error near unexpected token `;'", 1);
	else if (error == 16)
		ft_putendl_fd("syntax error near unexpected token `newline'", 1);
	if (error >= 12 && error <= 16)
		change_question(258, shell);
}

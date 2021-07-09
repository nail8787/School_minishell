#include "minishell.h"

int		check_syntax(t_shell *sh)
{
	int		i;
	int		flag;

	sh->command.err = 0;
	flag = 1;
	i = -1;
	while (sh->command.line[++i] && !sh->command.err)
	{
		skip_quotes_and_shield(sh->command.line, &i, &flag);
		if (sh->command.line[i] == ';')
			pipe_semicolon_case(sh, &flag, 15);
		else if (sh->command.line[i] == '|')
			pipe_semicolon_case(sh, &flag, 14);
		else if (sh->command.line[i] == '>')
			out_redirect_case(sh, &flag);
		else if (sh->command.line[i] == '<')
			in_redirect_case(sh, &flag);
		else if (sh->command.line[i] == ' ')
			flag = flag >= 4 && flag <= 6 ? 7 : flag;
		else
			flag = 0;
	}
	sh->command.err = flag > 2 && !sh->command.err ? 16 : sh->command.err;
	sh->command.err = flag == 1 && !sh->command.err ? 11 : sh->command.err;
	return (sh->command.err);
}

void	out_redirect_case(t_shell *shell, int *flag)
{
	if (*flag == 4)
		*flag = 5;
	else if (*flag == 5 || *flag == 7)
		shell->command.err = 12;
	else
		*flag = 4;
}

void	in_redirect_case(t_shell *shell, int *flag)
{
	if (*flag == 6 || *flag == 7)
		shell->command.err = 13;
	*flag = 6;
}

void	pipe_semicolon_case(t_shell *shell, int *flag, int error)
{
	if (*flag != 0)
		shell->command.err = error;
	if (error == 15)
		*flag = 2;
	else
		*flag = 3;
}

void	skip_quotes_and_shield(char *line, int *i, int *flag)
{
	int tmp;

	tmp = *i;
	skip_shield(line, i);
	skip_quotes(line, i, '\"');
	skip_quotes(line, i, '\'');
	if (tmp != *i)
		*flag = 0;
}

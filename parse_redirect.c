#include "minishell.h"

int		set_redirect(t_shell *shell, char ***word, int redirect)
{
	int		index;
	char	**out_files;
	char	**in_files;

	out_files = shell->command.out_file;
	in_files = shell->command.in_file;
	if (redirect == 1 || redirect == 2)
	{
		shell->command.out_append = redirect == 2;
		shell->command.out_file = word_append(out_files, &index);
		*word = &shell->command.out_file[index];
	}
	else if (redirect == 3)
	{
		shell->command.in_file = word_append(in_files, &index);
		*word = &shell->command.in_file[index];
	}
	return (0);
}

int		redirect_sym(t_shell *shell, int *i, int *redirect)
{
	char *line;

	line = shell->command.line;
	if (line[*i] && ft_strchr("<>", line[*i]) && *redirect == 0)
	{
		if (line[*i] == '>')
			*redirect = 1;
		else if (line[*i] == '<')
			*redirect = 3;
		(*i)++;
		if (line[*i] == '>' && *redirect == 1)
		{
			*redirect = 2;
			(*i)++;
		}
	}
	return (0);
}

#include "minishell.h"

int		split_line(t_shell *sh)
{
	char	**word;
	int		redirect;
	int		i;

	command_init_default(sh);
	i = 0;
	redirect = 0;
	while (sh->command.line[i])
	{
		create_arg(sh, &word, i, &redirect);
		add_sym_to_arg(sh, &word, &i);
		redirect_sym(sh, &i, &redirect);
		skip_space(sh->command.line, &i);
		if (multi_command(sh, &i))
			break ;
	}
	tilda(sh);
	if (!sh->command.line[i])
		sh->command.line = NULL;
	return (0);
}

int		skip_space(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
	return (0);
}

int		add_sym_to_arg(t_shell *shell, char ***word, int *i)
{
	char *line;

	line = shell->command.line;
	while (line[*i] && !ft_strchr(" |;<>", line[*i]))
	{
		special_sym(shell, word, line, i);
		if (ft_strchr(" $\'\"\\|;<>", line[*i]))
			continue ;
		sym_append(*word, line, i);
	}
	return (0);
}

int		create_arg(t_shell *shell, char ***word, int i, int *redirect_flag)
{
	char	*line;
	char	**words;
	int		index;

	words = shell->command.args;
	line = shell->command.line;
	if (is_new_word(line, i))
	{
		if (*redirect_flag != 0)
			set_redirect(shell, word, *redirect_flag);
		else
		{
			shell->command.args = word_append(words, &index);
			*word = &shell->command.args[index];
		}
		*redirect_flag = 0;
	}
	return (0);
}

int		multi_command(t_shell *shell, int *i)
{
	char *line;

	line = shell->command.line;
	if (line[*i] && ft_strchr(";|", line[*i]))
	{
		shell->command.line = line + *i + 1;
		if (line[*i] == '|')
			shell->command.right_pipe = 1;
		*i = 0;
		return (1);
	}
	else
		return (0);
}

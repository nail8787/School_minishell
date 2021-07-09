#include "minishell.h"

void	tilda(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->command.args[i])
	{
		if (ft_strcmp("~", shell->command.args[i]) == 0)
		{
			free(shell->command.args[i]);
			shell->command.args[i] = ft_strdup(shell->home);
		}
		i++;
	}
}

void	special_sym(t_shell *shell, char ***word, char *line, int *i)
{
	if (errno != 0)
		error_check(shell);
	shield(*word, line, i);
	single_quotes(*word, line, i);
	double_quotes(shell, word, line, i);
	dolla(shell, word, line, i);
}

void	shield(char **word, char *line, int *i)
{
	if (line[*i] == '\\')
	{
		(*i)++;
		if (line[*i])
			sym_append(word, line, i);
	}
}

void	single_quotes(char **word, char *line, int *i)
{
	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			sym_append(word, line, i);
		(*i)++;
	}
}

void	double_quotes(t_shell *shell, char ***word, char *line, int *i)
{
	if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\"')
		{
			shell->command.quotes = 1;
			if (line[*i] == '\\' && line[*i + 1] &&
				ft_strchr("\"\\$", line[*i + 1]))
				shield(*word, line, i);
			else if (line[*i] == '\\' && line[*i + 1])
				sym_append(*word, line, i);
			dolla(shell, word, line, i);
			if (line[*i] && !ft_strchr("\"\\$", line[*i]))
				sym_append(*word, line, i);
		}
		(*i)++;
		shell->command.quotes = 0;
	}
}

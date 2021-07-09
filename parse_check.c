#include "minishell.h"

int		is_new_word(char *line, int i)
{
	int is_first;
	int is_shielded;
	int	is_word;

	is_first = i == 0 && !ft_strchr(";| <>", line[i]);
	is_shielded = (i > 1 && line[i - 2] == '\\');
	is_shielded = is_shielded && i > 2 && line[i - 3] == '\\' ? 0 : is_shielded;
	is_word = is_first || (!is_shielded && (check_delimiter(";| <>", line, i)));
	return (is_word);
}

int		check_delimiter(char *delimiter, char *line, int i)
{
	if (i > 0)
		return (ft_strchr(delimiter, line[i - 1])
			&& !ft_strchr(delimiter, line[i]));
	else
		return (0);
}

void	skip_shield(char *line, int *i)
{
	if (line[*i] == '\\' && line[*i + 1])
		(*i) += 2;
}

void	skip_quotes(char *line, int *i, char quotes)
{
	if (line[*i] == quotes)
	{
		(*i)++;
		while (line[*i] && line[*i] != quotes)
		{
			skip_shield(line, i);
			(*i)++;
		}
		(*i)++;
	}
}

int		is_envvar_name(char *line, int i, int begin)
{
	if (i == begin && ft_isdigit(line[i]))
		return (0);
	if (ft_isalpha(line[i]) || ft_isdigit(line[i]) || line[i] == '_' ||
		line[i] == '?')
		return (1);
	else
		return (0);
}

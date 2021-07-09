#include "minishell.h"

void	dolla(t_shell *shell, char ***word, char *line, int *i)
{
	char	*var_name;
	char	*value;
	char	*tmp;

	if (line[*i] == '$' && (!line[*i + 1] || line[*i + 1] == ' ' ||
		(line[*i + 1] == '\"' && shell->command.quotes == 1)))
		sym_append(*word, line, i);
	else if (line[*i] == '$')
	{
		var_name = get_var_name(line, i);
		if ((value = get_env_val(shell, var_name)))
			value = ft_strdup(value);
		else
			value = ft_strdup("");
		free(var_name);
		if (!value)
			memory_alloc_error();
		tmp = **word;
		if (!(**word = ft_strjoin(**word, value)))
			memory_alloc_error();
		free(tmp);
		free(value);
	}
}

char	*get_var_name(char *line, int *i)
{
	char	*var_name;
	int		begin;

	var_name = word_init();
	(*i)++;
	begin = *i;
	while (line[*i] && is_envvar_name(line, *i, begin))
		sym_append(&var_name, line, i);
	return (var_name);
}

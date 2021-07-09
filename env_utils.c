#include "minishell.h"

char	**copy_env(char **envv)
{
	int		len;
	int		i;
	char	**env;

	len = 0;
	while (envv[len])
		len++;
	if (!(env = (char**)malloc(sizeof(char*) * (len + 1))))
		memory_alloc_error();
	env[len] = NULL;
	i = 0;
	while (i < len)
	{
		if (!(env[i] = ft_strdup(envv[i])))
			memory_alloc_error();
		i++;
	}
	return (env);
}

char	*get_env_val(t_shell *shell, char *name)
{
	int		i;
	int		name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (shell->env[i])
	{
		if (ft_strncmp(name, shell->env[i], name_len) == 0)
			if (shell->env[i][name_len] == '=')
				return (shell->env[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

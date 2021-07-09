#include "minishell.h"

int			check_if_key_exists(char *str, char **env_old)
{
	int		i;
	int		len_key;

	i = 0;
	len_key = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		else
		{
			i++;
			len_key++;
		}
	}
	i = 0;
	while (env_old[i])
	{
		if (ft_strncmp(str, env_old[i], len_key) == 0)
			return (i);
		else
			i++;
	}
	return (-1);
}

static char	**change_existed_key(char *str, char **env_old, int i)
{
	char	*tmp;

	if (check_if_value_exists(str) == 0)
		return (env_old);
	tmp = env_old[i];
	if (!(env_old[i] = ft_strdup(str)))
		memory_alloc_error();
	free(tmp);
	return (env_old);
}

char		**export_add_key(char *str, char **env_old)
{
	int		len_env_p;
	int		i;
	char	**env_new;

	if ((i = check_if_key_exists(str, env_old)) != -1)
		return (change_existed_key(str, env_old, i));
	len_env_p = 0;
	i = 0;
	while (env_old[i++])
		len_env_p++;
	i = -1;
	if (!(env_new = (char **)malloc(sizeof(char*) * (len_env_p + 2))))
		memory_alloc_error();
	env_new[len_env_p + 1] = NULL;
	while (env_old[++i])
		if (!(env_new[i] = ft_strdup(env_old[i])))
			memory_alloc_error();
	if (!(env_new[i] = ft_strdup(str)))
		memory_alloc_error();
	i = 0;
	while (env_old[i])
		free(env_old[i++]);
	free(env_old);
	return (env_new);
}

int			check_for_iden(char *str, t_shell *shell)
{
	if (*str)
		if (!(shell->error.err_iden = ft_strdup(str)))
			memory_alloc_error();
	if (ft_isalpha(*str) == 0 && *str != '_')
		return (-2);
	while (*str)
	{
		if (ft_isalnum(*str) == 0 && !ft_strchr(" _=/:.-\\", *str))
			return (-2);
		else
			str++;
	}
	free(shell->error.err_iden);
	shell->error.err_iden = NULL;
	return (0);
}

int			ft_export(char *str, t_shell *shell)
{
	if (str)
		if (check_for_iden(str, shell) < 0)
		{
			errno = 129;
			error_check(shell);
			errno = -1;
			return (1);
		}
	if (!str)
		export_no_args(shell->env);
	else
		shell->env = export_add_key(str, shell->env);
	return (0);
}

#include "minishell.h"

void	check_for_oldpwd(t_shell *shell)
{
	char	*oldpwd;

	if (check_if_key_exists("OLDPWD", shell->env) == -1)
	{
		if (!(oldpwd = ft_strdup("OLDPWD")))
			memory_alloc_error();
		ft_export("OLDPWD", shell);
		free(oldpwd);
	}
}

char	*trim_last_part_of_path(char **env_copy)
{
	int		res;
	t_cd	cd;
	char	*str_new;
	char	*tmp;
	int		len;

	cd.pwd_i = check_if_key_exists("PWD", env_copy);
	tmp = ft_strrchr(env_copy[cd.pwd_i], '/');
	len = tmp ? ft_strlen(tmp) : 0;
	res = ((ft_strlen(env_copy[cd.pwd_i]) - 4) - len);
	if (!(str_new = ft_substr(env_copy[cd.pwd_i], 4, res)))
		memory_alloc_error();
	if (ft_strlen(str_new) == 0)
	{
		free(str_new);
		if (!(str_new = ft_strdup("/")))
			memory_alloc_error();
	}
	return (str_new);
}

char	*get_home_path(char **env_copy, t_shell *shell)
{
	t_cd	cd;
	char	*str_home;

	cd.home_i = check_if_key_exists("HOME", env_copy);
	if (cd.home_i == -1)
	{
		if (!(str_home = ft_strdup(shell->home)))
			memory_alloc_error();
	}
	else if (!(str_home = ft_strdup(&env_copy[cd.home_i][5])))
		memory_alloc_error();
	return (str_home);
}

char	*prev_dir(char **env_copy)
{
	t_cd	cd;
	char	*str_prev;

	cd.oldpwd_i = check_if_key_exists("OLDPWD", env_copy);
	if (cd.oldpwd_i == -1 || check_if_value_exists(env_copy[cd.oldpwd_i]) == 0)
		return (NULL);
	else
	{
		if (!(str_prev = ft_strdup(&env_copy[cd.oldpwd_i][7])))
			memory_alloc_error();
		return (str_prev);
	}
}

int		error_cd(t_shell *shell, t_cd *cd)
{
	chdir(cd->start_pwd);
	free_mass(shell->env);
	shell->env = cd->temp_env;
	return (errno);
}

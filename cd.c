#include "minishell.h"

char		**absolute_or_home_path(char *str, char **env_copy)
{
	t_cd	cd;

	cd.oldpwd_i = check_if_key_exists("OLDPWD", env_copy);
	cd.pwd_i = check_if_key_exists("PWD", env_copy);
	if (!(cd.oldpwd = ft_strjoin("OLD", env_copy[cd.pwd_i])))
		memory_alloc_error();
	cd.env_new = export_add_key(cd.oldpwd, env_copy);
	free(cd.oldpwd);
	if (!(cd.pwd = ft_strjoin("PWD=", str)))
		memory_alloc_error();
	cd.env_new = export_add_key(cd.pwd, cd.env_new);
	free(cd.pwd);
	free(str);
	return (cd.env_new);
}

static char	**chg_abs_env_path(char **env_copy)
{
	char	*buf;

	if (!(buf = getcwd(NULL, 0)))
		memory_alloc_error();
	env_copy = absolute_or_home_path(buf, env_copy);
	return (env_copy);
}

char		**chg_env_paths(char **env_copy, char *str,
							t_cd cd, t_shell *shell)
{
	if ((!str) || ft_strcmp(str, "..") == 0 || ft_strcmp(str, "-") == 0 ||
			ft_strcmp(str, ".") == 0)
		env_copy = absolute_or_home_path(cd.str_tmp, env_copy);
	else if (str[0] == '/')
	{
		env_copy = chg_abs_env_path(env_copy);
		free(cd.str_tmp);
	}
	else
	{
		env_copy = relative_path(cd.str_args, env_copy, shell);
		free_mass(cd.str_args);
	}
	return (env_copy);
}

int			ft_cd(char *str, t_shell *shell)
{
	int		res;
	t_cd	cd;

	cd.start_pwd = get_env_val(shell, "PWD");
	cd.temp_env = copy_env(shell->env);
	if (!str)
		res = cd_chdir_tilda(shell, &cd);
	else if (str[0] == '/')
		res = cd_chdir_absolute(&cd, str);
	else if (ft_strncmp(str, "..", 3) == 0)
		res = cd_chdir_dot_dot(shell, &cd);
	else if (ft_strncmp(str, "-", 2) == 0)
		res = cd_chdir_minus(shell, &cd);
	else if (ft_strcmp(str, ".") == 0)
		res = cd_chdir_dot(&cd);
	else
		res = cd_chdir_relative(&cd, str, shell);
	if (res != 0)
		return (error_cd(shell, &cd));
	else
		shell->env = chg_env_paths(shell->env, str, cd, shell);
	free_mass(cd.temp_env);
	return (0);
}

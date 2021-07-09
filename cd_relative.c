#include "minishell.h"

char		**change_relative_path(char *str, char **env_copy)
{
	t_cd	cd;
	char	*tmp;

	cd.pwd_i = check_if_key_exists("PWD", env_copy);
	tmp = env_copy[cd.pwd_i];
	if (!(env_copy[cd.pwd_i] = ft_strjoin(env_copy[cd.pwd_i], "/")))
		memory_alloc_error();
	free(tmp);
	if (!(cd.pwd = ft_strjoin(env_copy[cd.pwd_i], str)))
		memory_alloc_error();
	cd.env_new = export_add_key(cd.pwd, env_copy);
	free(cd.pwd);
	return (cd.env_new);
}

static void	relative_path_cont(char **str_args, t_cd *cd, t_shell *shell)
{
	char	*str;

	while (*str_args)
	{
		if (ft_strncmp(*str_args, "..", 2) == 0)
		{
			str = trim_last_part_of_path(cd->env_new);
			cd->env_new = absolute_or_home_path(str, cd->env_new);
		}
		else if (ft_strncmp(*str_args, "~", 2) == 0)
		{
			str = get_home_path(cd->env_new, shell);
			cd->env_new = absolute_or_home_path(str, cd->env_new);
		}
		else if (ft_strcmp(*str_args, ".") == 0)
		{
			if (!(str = getcwd(NULL, 0)))
				memory_alloc_error();
			cd->env_new = absolute_or_home_path(str, cd->env_new);
		}
		else
			cd->env_new = change_relative_path(*str_args, cd->env_new);
		str_args++;
	}
}

char		**relative_path(char **str_args, char **env_copy, t_shell *shell)
{
	t_cd	cd;

	cd.oldpwd_i = check_if_key_exists("OLDPWD", env_copy);
	cd.pwd_i = check_if_key_exists("PWD", env_copy);
	if (!(cd.oldpwd = ft_strjoin("OLD", env_copy[cd.pwd_i])))
		memory_alloc_error();
	cd.env_new = export_add_key(cd.oldpwd, env_copy);
	relative_path_cont(str_args, &cd, shell);
	cd.env_new = export_add_key(cd.oldpwd, cd.env_new);
	free(cd.oldpwd);
	return (cd.env_new);
}

int			cd_chdir_relative(t_cd *cd, char *str, t_shell *shell)
{
	int	res;

	if (!(cd->str_args = ft_split(str, '/')))
		memory_alloc_error();
	res = chdir_relative(cd->str_args, shell->env, shell);
	if (res != 0)
		free_mass(cd->str_args);
	return (res);
}

int			chdir_relative(char **str_args, char **env_copy, t_shell *shell)
{
	int		res;
	char	*tmp_pwd;

	tmp_pwd = pwd_save();
	if (*str_args[0] == '~')
	{
		res = chdir_relative_tilda(env_copy, shell);
		str_args++;
		if (res != 0)
			return (res);
	}
	res = cd_chdir_relative_cycle(str_args, env_copy);
	env_copy = export_add_key(tmp_pwd, env_copy);
	free(tmp_pwd);
	return (res);
}

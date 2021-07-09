#include "minishell.h"

int		chdir_relative_dot(void)
{
	char	*tmp;
	int		res;

	if (!(tmp = getcwd(NULL, 0)))
		memory_alloc_error();
	res = chdir(tmp);
	free(tmp);
	return (res);
}

int		chdir_relative_tilda(char **env_copy, t_shell *shell)
{
	int		res;
	char	*tmp;

	tmp = get_home_path(env_copy, shell);
	res = chdir(tmp);
	env_copy = absolute_or_home_path(tmp, env_copy);
	return (res);
}

int		chdir_relative_dot_dot(char **env_copy)
{
	int		res;
	char	*tmp;

	tmp = trim_last_part_of_path(env_copy);
	res = chdir(tmp);
	env_copy = absolute_or_home_path(tmp, env_copy);
	return (res);
}

char	*pwd_save(void)
{
	char	*pwd;
	char	*tmp_pwd;

	if (!(pwd = getcwd(NULL, 0)))
		memory_alloc_error();
	if (!(tmp_pwd = ft_strjoin("PWD=", pwd)))
		memory_alloc_error();
	free(pwd);
	return (tmp_pwd);
}

int		cd_chdir_relative_cycle(char **str_args, char **env_copy)
{
	int	res;

	while (*str_args)
	{
		if ((ft_strncmp(*str_args, "..", 3) == 0))
			res = chdir_relative_dot_dot(env_copy);
		else if (ft_strcmp(*str_args, ".") == 0)
			res = chdir_relative_dot();
		else
			res = chdir(*str_args);
		if (res != 0)
			return (res);
		str_args++;
	}
	return (res);
}

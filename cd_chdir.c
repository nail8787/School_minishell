#include "minishell.h"

int	cd_chdir_tilda(t_shell *shell, t_cd *cd)
{
	cd->str_tmp = get_home_path(shell->env, shell);
	return (chdir(cd->str_tmp));
}

int	cd_chdir_dot_dot(t_shell *shell, t_cd *cd)
{
	cd->str_tmp = trim_last_part_of_path(shell->env);
	return (chdir(cd->str_tmp));
}

int	cd_chdir_absolute(t_cd *cd, char *str)
{
	if (!(cd->str_tmp = ft_strdup(str)))
		memory_alloc_error();
	return (chdir(cd->str_tmp));
}

int	cd_chdir_dot(t_cd *cd)
{
	if (!(cd->str_tmp = getcwd(NULL, 0)))
		memory_alloc_error();
	return (chdir(cd->str_tmp));
}

int	cd_chdir_minus(t_shell *shell, t_cd *cd)
{
	int res;

	cd->str_tmp = prev_dir(shell->env);
	if (!cd->str_tmp)
	{
		errno = 128;
		return (1);
	}
	res = chdir(cd->str_tmp);
	ft_putendl_fd(cd->str_tmp, 1);
	return (res);
}

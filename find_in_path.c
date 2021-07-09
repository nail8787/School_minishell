#include "minishell.h"

static char	*path_malloc(t_shell *shell, int i, char **split_path)
{
	char	*pathname;
	char	*tmp;

	if (!(pathname = ft_strjoin(split_path[i], "/")))
		memory_alloc_error();
	tmp = pathname;
	if (!(pathname = ft_strjoin(pathname, shell->command.args[0])))
		memory_alloc_error();
	free(tmp);
	return (pathname);
}

static int	check_in_path_while(int i, char **split_path,
	t_shell *shell)
{
	char		*pathname;
	struct stat stats;
	int			status;

	while (split_path[i])
	{
		pathname = path_malloc(shell, i, split_path);
		if (stat(pathname, &stats) == 0)
		{
			status = start_binary(pathname, shell->command.args, shell->env);
			free(pathname);
			free_mass(split_path);
			change_question(status, shell);
			errno = -2;
			return (0);
		}
		else
			i++;
		free(pathname);
	}
	return (-2);
}

int			check_in_path(t_shell *shell)
{
	char	**split_path;
	int		i;

	i = check_if_key_exists("PATH=", shell->env);
	if (i < 0)
		return (-2);
	if (!(split_path = ft_split(&shell->env[i][5], ':')))
		memory_alloc_error();
	i = 0;
	if (check_in_path_while(i, split_path, shell) != -2)
		return (0);
	free_mass(split_path);
	return (-2);
}

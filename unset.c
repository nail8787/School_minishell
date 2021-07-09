#include "minishell.h"

static char	**unset_key(int i, char **env_copy)
{
	int		count;
	char	**env_new;
	int		j;

	j = 0;
	count = 0;
	while (env_copy[count])
		count++;
	if (!(env_new = (char **)malloc(count * sizeof(char *))))
		memory_alloc_error();
	env_new[count - 1] = NULL;
	count = 0;
	while (env_copy[count])
	{
		if (count == i)
			count++;
		else
			env_new[j++] = env_copy[count++];
	}
	free(env_copy[i]);
	free(env_copy);
	return (env_new);
}

int			ft_unset(char *str, t_shell *shell)
{
	int	i;

	if (str)
		if (check_for_iden(str, shell) < 0)
		{
			errno = 129;
			error_check(shell);
			errno = -1;
			return (1);
		}
	if ((i = check_if_key_exists(str, shell->env)) != -1)
	{
		shell->env = unset_key(i, shell->env);
		return (0);
	}
	else
		return (0);
}

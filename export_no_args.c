#include "minishell.h"

static char	**sort_export(char **env_copy)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env_copy[i])
	{
		j = i + 1;
		while (env_copy[j] && ft_strncmp(env_copy[i],
			env_copy[j], ft_strlen(env_copy[j])) <= 0)
			j++;
		if (env_copy[j] && ft_strncmp(env_copy[i],
			env_copy[j], ft_strlen(env_copy[j])) > 0)
		{
			tmp = env_copy[i];
			env_copy[i] = env_copy[j];
			env_copy[j] = tmp;
		}
		else
			i++;
	}
	return (env_copy);
}

static void	print_export(char **env_copy, int i, int j)
{
	while (env_copy[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while ((env_copy[i][j] != '=') && env_copy[i][j])
			ft_putchar_fd(env_copy[i][j++], 1);
		if (!env_copy[i][j])
		{
			ft_putchar_fd('\n', 1);
			i++;
			continue ;
		}
		ft_putchar_fd(env_copy[i][j++], 1);
		ft_putchar_fd('\"', 1);
		if (env_copy[i][j] == '\"')
		{
			ft_putstr_fd("\\\"", 1);
			j++;
		}
		while (env_copy[i][j] != '\0' && env_copy[i][j])
			ft_putchar_fd(env_copy[i][j++], 1);
		ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void		export_no_args(char **env_copy)
{
	int	i;
	int j;

	i = 1;
	j = 0;
	env_copy = sort_export(env_copy);
	print_export(env_copy, i, j);
}

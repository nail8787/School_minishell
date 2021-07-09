#include "minishell.h"

void	memory_alloc_error(void)
{
	ft_putendl_fd("Memory allocation error", 1);
	exit(12);
}

void	free_command_struct(t_shell *shell)
{
	free_mass(shell->command.args);
	free_mass(shell->command.in_file);
	free_mass(shell->command.out_file);
}

void	free_mass(char **mass)
{
	int i;

	i = 0;
	if (!mass)
		return ;
	while (mass[i])
	{
		free(mass[i]);
		mass[i] = NULL;
		i++;
	}
	free(mass);
	mass = NULL;
}

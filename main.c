#include "minishell.h"

int		main(int argc, char **argv, char **envv)
{
	t_shell		shell;

	shell.env = copy_env(envv);
	check_for_oldpwd(&shell);
	argc = 0;
	argv = NULL;
	get_home(&shell);
	shell.env = export_add_key("?=0", shell.env);
	shell.pipe.temp_fd0 = dup(0);
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_slash_handler);
	line_handler(&shell);
	normal_exit(&shell);
	return (0);
}

void	get_home(t_shell *shell)
{
	char	*home;

	home = get_env_val(shell, "HOME");
	if (home)
		shell->home = ft_strdup(home);
	else
		shell->home = getcwd(NULL, 0);
}

void	line_handler(t_shell *shell)
{
	char	*command;

	ft_putstr_fd("minishell> ", 1);
	while (get_next_line(0, &command))
	{
		shell->command.line = command;
		shell->command.right_pipe = 0;
		if (!check_syntax(shell))
			while (shell->command.line)
				exec_command(shell);
		else
			print_syntax_error(shell->command.err, shell);
		free(command);
		ft_putstr_fd("minishell> ", 1);
	}
}

void	exec_command(t_shell *shell)
{
	split_line(shell);
	if (shell->command.right_pipe == 1 || *shell->command.out_file ||
		*shell->command.in_file)
		check_for_pipe_and_rd(shell);
	else if (shell->command.args[0])
	{
		choose_cmd(shell);
		dup2(shell->pipe.temp_fd0, 0);
	}
	free_command_struct(shell);
}

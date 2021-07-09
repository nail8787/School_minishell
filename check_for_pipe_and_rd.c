#include "minishell.h"

int		open_fd(t_shell *shell)
{
	int fd;
	int i;

	i = 0;
	fd = -1;
	if (shell->command.out_append == 0)
		while (shell->command.out_file[i])
			fd = open(shell->command.out_file[i++], O_WRONLY |
				O_CREAT | O_TRUNC, 0666);
	else if (shell->command.out_append == 1)
		while (shell->command.out_file[i])
			fd = open(shell->command.out_file[i++], O_RDWR | O_APPEND |
				O_CREAT, 0666);
	return (fd);
}

void	is_right_redirect(t_shell *shell)
{
	int fd;
	int pid;
	int status;

	if ((fd = open_fd(shell)) == -1)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		dup2(fd, 1);
		if (choose_cmd(shell) == 1)
			exit(0);
	}
	else
	{
		wait(&status);
		errno = 0;
		close(fd);
	}
}

int		in_open_fd(t_shell *shell, int fd)
{
	int	i;

	i = 0;
	while (shell->command.in_file[i])
	{
		fd = open(shell->command.in_file[i++], O_RDONLY);
		if (fd == -1)
		{
			if (errno != 0)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(shell->command.in_file[--i], 2);
				ft_putstr_fd(": ", 2);
				ft_putendl_fd(strerror(errno), 2);
			}
			return (-1);
		}
	}
	return (fd);
}

void	is_left_redirect(t_shell *shell)
{
	int fd;
	int	status;
	int pid;

	fd = -1;
	if ((fd = in_open_fd(shell, fd)) == -1)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		dup2(fd, 0);
		if (*shell->command.out_file)
			if (child_left_redir(shell) == -1)
				exit(0);
		choose_cmd(shell);
		exit(0);
	}
	else
	{
		wait(&status);
		close(fd);
	}
}

void	check_for_pipe_and_rd(t_shell *shell)
{
	if (shell->command.right_pipe == 1)
		is_pipe(shell);
	else if (*shell->command.in_file)
		is_left_redirect(shell);
	else if (*shell->command.out_file)
		is_right_redirect(shell);
	if (shell->command.right_pipe != 1)
		dup2(shell->pipe.temp_fd0, 0);
}

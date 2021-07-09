#include "minishell.h"

int			child_left_redir(t_shell *shell)
{
	int fd;

	if ((fd = open_fd(shell)) == -1)
		return (-1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

static void	child_pipe(t_shell *shell, int fd)
{
	dup2(shell->pipe.fds[1], 1);
	close(shell->pipe.fds[0]);
	if (*shell->command.in_file)
	{
		if ((fd = in_open_fd(shell, fd)) == -1)
			return ;
		dup2(fd, 0);
	}
	else if (*shell->command.out_file)
	{
		if ((fd = open_fd(shell)) == -1)
			return ;
		dup2(fd, 1);
	}
	choose_cmd(shell);
	if (fd != -1)
		close(fd);
	close(shell->pipe.fds[1]);
	exit(0);
}

void		is_pipe(t_shell *shell)
{
	int	pid;
	int	status;
	int	fd;

	fd = -1;
	if (!(shell->pipe.fds = (int *)malloc(sizeof(int) * 2)))
		memory_alloc_error();
	if (pipe(shell->pipe.fds) != 0)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		child_pipe(shell, fd);
	}
	else
	{
		dup2(shell->pipe.fds[0], 0);
		close(shell->pipe.fds[1]);
		wait(&status);
		close(shell->pipe.fds[0]);
		free(shell->pipe.fds);
	}
}

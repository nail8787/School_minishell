#include "minishell.h"

int		signaled(int status)
{
	if (WTERMSIG(status) == 3)
	{
		errno = 128 + 3;
		write(1, "Quit: 3\n", 8);
	}
	else if (WTERMSIG(status) == 2)
	{
		errno = 128 + 2;
		write(1, "\n", 1);
	}
	return (errno);
}

int		start_binary(char *pathname, char **args, char **envs)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (errno);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(pathname, args, envs) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		signals_init();
		if (WIFEXITED(status) != 0)
			return (WEXITSTATUS(status));
		if (WIFSIGNALED(status) != 0)
			return (signaled(status));
	}
	return (0);
}

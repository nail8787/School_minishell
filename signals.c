#include "minishell.h"

void	ctrl_c_handler(int num)
{
	num = 0;
	write(1, "\b\b  \b\b", 6);
	errno = -1;
	write(1, "\nminishell> ", 12);
}

void	ctrl_slash_handler(int num)
{
	num = 0;
	write(1, "\b\b  \b\b", 6);
}

void	signals_init(void)
{
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_slash_handler);
}

#include "minishell.h"

int		ft_pwd(void)
{
	char	*buf;

	if (!(buf = getcwd(NULL, 0)))
		memory_alloc_error();
	ft_putendl_fd(buf, 1);
	free(buf);
	return (1);
}

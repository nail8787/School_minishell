#include "minishell.h"

static char	*add_buf(char *line, char *buf)
{
	char *tmp;

	if (line)
	{
		tmp = ft_strjoin(line, buf);
		free(line);
		line = NULL;
		line = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
	}
	else
		line = ft_strdup(buf);
	return (line);
}

static char	*separate_rest(char **line, ssize_t size)
{
	size_t	i;
	char	*tmp;
	char	*rest;
	size_t	len;

	if (!*line)
		return (NULL);
	len = ft_strlen(*line);
	i = 0;
	while ((*line)[i] != '\n' && i < len)
		i++;
	if (i < len)
	{
		tmp = ft_substr(*line, 0, i);
		rest = ft_substr(*line, i + 1, len);
		free(*line);
		*line = NULL;
		*line = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
		return (rest);
	}
	else if (size == 0)
		return (NULL);
	return (*line);
}

int			end_of_file(char **line, char *rest)
{
	if (!*line)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (!rest)
		return (0);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char	*rest;
	char		buffer[32 + 1];
	ssize_t		size;

	if (fd < 0 || !line || read(fd, buffer, 0) != 0)
		return (-1);
	*line = rest;
	buffer[0] = '\0';
	while ((size = read(fd, buffer, 1)) || buffer[0])
	{
		if (size == 0 && *line)
		{
			buffer[1] = '\0';
			write(1, "  \b\b", 4);
			continue;
		}
		buffer[size] = '\0';
		if (!(*line = add_buf(*line, buffer)))
			return (-1);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	rest = separate_rest(line, size);
	return (end_of_file(line, rest));
}

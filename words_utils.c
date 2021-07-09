#include "minishell.h"

char	**word_append(char **words, int *index)
{
	char	**new_;

	*index = words_len(words);
	if (!(new_ = (char**)malloc(sizeof(char*) * (*index + 2))))
		memory_alloc_error();
	new_ = words_cpy(new_, words);
	new_[*index] = word_init();
	new_[*index + 1] = NULL;
	free(words);
	words = NULL;
	return (new_);
}

int		words_len(char **words)
{
	int len;

	len = 0;
	while (words[len])
		len++;
	return (len);
}

char	**words_cpy(char **dest, char **src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

int		sym_append(char **word, char *line, int *i)
{
	int		len;
	char	*new;

	len = ft_strlen(*word);
	if (!(new = (char*)malloc(len + 2)))
		memory_alloc_error();
	new = ft_memcpy(new, *word, len);
	new[len] = line[*i];
	new[len + 1] = 0;
	free(*word);
	*word = NULL;
	*word = new;
	(*i)++;
	return (0);
}

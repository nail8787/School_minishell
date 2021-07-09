#include "libft.h"

static int	word_count(const char *str, char c)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if ((i == 0 && str[i] != c) ||
		(i != 0 && str[i - 1] == c && str[i] != c))
			count++;
		i++;
	}
	return (count);
}

static int	word_len(const char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static void	free_mem(char **words, int word)
{
	int i;

	i = 0;
	while (i < word)
	{
		free(words[word]);
		word++;
	}
	free(words);
}

static char	**fill(const char *s, char c, int count)
{
	int		i;
	int		len;
	int		word;
	char	**words;

	if (!(words = (char**)malloc(sizeof(char*) * count + 1)))
		return (NULL);
	i = 0;
	word = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || (i != 0 && s[i - 1] == c && s[i] != c))
		{
			len = word_len(s + i, c) + 1;
			if (!(words[word] = (char*)malloc(sizeof(char) * len)))
			{
				free_mem(words, word);
				return (NULL);
			}
			ft_strlcpy(words[word], s + i, len);
			word++;
		}
		i++;
	}
	return (words);
}

char		**ft_split(const char *str, char c)
{
	int		count;
	char	**words;

	if (!str)
		return (NULL);
	count = word_count(str, c);
	if (!(words = fill(str, c, count)))
		return (NULL);
	words[count] = NULL;
	return (words);
}

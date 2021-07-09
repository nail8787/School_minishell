#include "minishell.h"

char	**words_init(void)
{
	char **words;

	if (!(words = (char**)malloc(sizeof(char*))))
		memory_alloc_error();
	words[0] = NULL;
	return (words);
}

char	*word_init(void)
{
	char *word;

	if (!(word = (char*)malloc(1)))
		memory_alloc_error();
	word[0] = 0;
	return (word);
}

int		command_init_default(t_shell *shell)
{
	shell->command.left_pipe = shell->command.right_pipe;
	shell->command.right_pipe = 0;
	shell->command.out_file = words_init();
	shell->command.in_file = words_init();
	shell->command.args = words_init();
	shell->command.err = 0;
	shell->command.quotes = 0;
	shell->command.out_append = 0;
	return (0);
}

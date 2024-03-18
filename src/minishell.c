#include "minishell.h"

int	main(int argc, char **argv)
{
	t_token	*token_list;
	char *line;

	token_list = NULL;
	(void)argv;
	if (argc > 1)
		return (1);
	int i = 0;
	while (i++ < 5)
	{
		line = readline("minishell$ ");
		if (!line)
			ft_error("readline", errno);
//		printf("line %d: %s\n", i, line);
		lexer_token(line);
		add_history(line);
		free(line);
	}
	return (0);
}

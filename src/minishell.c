#include "minishell.h"

int	tools_init(t_tools *tools)
{
	tools->envp = NULL;
	tools->str = NULL;
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	char 	*line;

	(void)argv;
	(void)envp;
	if (argc > 1)
		return (1);
	int i = 0;
	tools_init(&tools);
	tools.envp = ft_arrdup(envp);
	while (i++ < 5)
	{
		line = readline("minishell$ ");
		if (!line)
			ft_error("readline", errno);
		if (!count_quotes(line))
			ft_error("unclosed quotes", errno);
//		printf("line %d: %s\n", i, line);
		lexer_token(&tools, line);
		while (tools.lexer_list != NULL)
		{
			printf("type: %d\n str: %s\n indx: %d\n ----\n", tools.lexer_list->type, tools.lexer_list->str, tools.lexer_list->indx);
			tools.lexer_list = tools.lexer_list->next;
		}
/*		while (*tools.envp != NULL)
			printf("--> %s\n", *tools.envp++);*/
		add_history(line);
		free(line);
	}
	return (0);
}

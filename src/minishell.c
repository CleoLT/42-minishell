#include "minishell.h"

int	tools_init(t_tools *tools, char **envp)
{
	tools->envp = ft_arrdup(envp);
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
	tools_init(&tools, envp);
	while (i++ < 5)
	{
		line = readline("minishell$ ");
		if (!line)
			ft_error("readline", errno);
		if (!count_quotes(line))
			ft_error("unclosed quotes", errno);
//		printf("line %d: %s\n", i, line);
		lexer_token(&tools, line);
/*		if (!envp_reader(&tools))
			ft_error("bad envp_reader", errno);*/
/*		while (tools.lexer_list != NULL)
		{
			printf("type: %d\n str: %s\n indx: %d\n ----\n", tools.lexer_list->type, tools.lexer_list->str, tools.lexer_list->indx);
			tools.lexer_list = tools.lexer_list->next;
		}*/
/*		while (tools.envp_list != NULL)
		{
			printf(" name: %s\n value: %s\n -----\n", tools.envp_list->name, tools.envp_list->value);
			tools.envp_list = tools.envp_list->next;
		}*/
/*		while (*tools.envp != NULL)
			printf("--> %s\n", *tools.envp++);*/
		add_history(line);
		free(line);
	}
	return (0);
}

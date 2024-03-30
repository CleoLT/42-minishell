#include "minishell.h"

static void cmd_faker(t_tools *tools, char *line)
{
	t_cmd *comm;
	comm = malloc(sizeof(t_cmd));
	comm->arg = ft_split(line, ' ');
	tools->cmd = comm;
	int i = 0;
	while (tools->cmd->arg[i])
			printf("%s ", tools->cmd->arg[i++]);
	printf("| ");

	t_cmd *comm1;
	comm1 = malloc(sizeof(t_cmd));
	comm1->arg = ft_split(" wc -l   ", ' ');
	tools->cmd->next = comm1;
	i = 0;
	while (tools->cmd->next->arg[i])
			printf("%s ", tools->cmd->next->arg[i++]);
	printf("| ");

	t_cmd *comm2;
	comm2 = malloc(sizeof(t_cmd));
	comm2->arg = ft_split(" cat ", ' ');
	comm1->next = comm2;
	i = 0;
	while (tools->cmd->next->next->arg[i])
			printf("%s ", tools->cmd->next->next->arg[i++]);
	printf("\n");

	tools->cmd->next->next->next = NULL;

}

int	tools_init(t_tools *tools, char **envp)
{
	tools->envp = NULL;
	tools->str = NULL;
	tools->path = get_path_env(envp);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	char 	*line;

	(void)argv;
	if (argc > 1)
		return (1);
	int i = 0;
	tools_init(&tools, envp);
	tools.envp = ft_arrdup(envp);
	while (i++ < 5)
	{
		line = readline("minishell$ ");
		if (!line)
			ft_error("readline error", errno);
		if (!count_quotes(line))
			ft_error("unclosed quotes", errno);
//		printf("que pasa");
//		printf("line %d: %s\n", i, line);
/*		lexer_token(&tools, line);
		while (tools.lexer_list != NULL)
		{
			printf("type: %d\n str: %s\n indx: %d\n ----\n", tools.lexer_list->type, tools.lexer_list->str, tools.lexer_list->indx);

			printf("\npointer: %p\n", tools.lexer_list);	//lexer_list da leaks de memoria
			tools.lexer_list = tools.lexer_list->next;
		}
		*/
/*		while (*tools.envp != NULL)
			printf("--> %s\n", *tools.envp++);*/
		cmd_faker(&tools, line);
		execute(&tools);
		add_history(line);
		free(line);
		free(tools.str);
	//	free_arr(tools.cmd->arg); // free faker 
	//	free(tools.cmd); //free faker 
	}
	free_arr(tools.envp);
	free_arr(tools.path);
	return (0);
}

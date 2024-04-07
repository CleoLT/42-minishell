/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:38:25 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/07 18:58:47 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void cmd_faker(t_tools *tools, char *line)
{
	t_cmd *comm;
	comm = malloc(sizeof(t_cmd));
	comm->arg = ft_split(line, ' ');
	tools->cmd = comm;
	tools->cmd->fd_in = 0;
	tools->cmd->fd_out = 1;
	tools->cmd->prev = NULL; 

	tools->cmd->next = NULL;
	tools->t_cmd_size = 1;

/*	int i = 0;
	while (tools->cmd->arg[i])
			printf("%s ", tools->cmd->arg[i++]);
	printf("| ");

	t_cmd *comm1;
	comm1 = malloc(sizeof(t_cmd));
	comm1->arg = ft_split(" cat", ' ');
	tools->cmd->next = comm1;
	tools->cmd->next->fd_in = 0;
	tools->cmd->next->fd_out = 1;
	tools->cmd->next->prev = tools->cmd; 
	i = 0;
	while (tools->cmd->next->arg[i])
			printf("%s ", tools->cmd->next->arg[i++]);
	printf("| ");

	t_cmd *comm2;
	comm2 = malloc(sizeof(t_cmd));
	comm2->arg = ft_split(" cat", ' ');
	comm1->next = comm2;
	tools->cmd->next->next->fd_in = 0;
	tools->cmd->next->next->fd_out = 1;
	tools->cmd->next->next->prev = tools->cmd->next; 
	i = 0;
	while (tools->cmd->next->next->arg[i])
			printf("%s ", tools->cmd->next->next->arg[i++]);
	printf("\n");

	tools->cmd->next->next->next = NULL;
	tools->t_cmd_size = 3;
*/
}

int	tools_init(t_tools *tools, char **envp)
{
	tools->envp = ft_arrdup(envp);
	tools->str = NULL;
	tools->envp_list = NULL;
	tools->lexer_list = NULL;
	tools->path = get_path_env(envp);
	tools->exit_code = 0;
//	signals();
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	char 	*line;

	(void)argv;
	if (argc > 1)
		return (1);
//	int i = 0;
	tools_init(&tools, envp);
	while (1)
	{
		line = readline("\033[0;32mminishell$ \033[0m");
		if (!line)
		{
			ft_error("readline error", errno);
			write(2, "readline wtf", 20);
		}
		if (!count_quotes(line))
		{
			write(2, "error: unclosed quotes\n", 23);
			free(line);
			continue ;
		}
	//	printf("line %d: %s\n", i, line);
	//	lexer_token(&tools, line);
/*		if (!envp_reader(&tools))
			ft_error("bad envp_reader", errno);*/
/*		while (tools.lexer_list != NULL)
		{
			printf("type: %d\n str: %s\n indx: %d\n ----\n", tools.lexer_list->type, tools.lexer_list->str, tools.lexer_list->indx);

//			printf("\npointer: %p\n", tools.lexer_list);	//lexer_list da leaks de memoria
			tools.lexer_list = tools.lexer_list->next;
		}*/
/*		while (tools.envp_list != NULL)
		{
			printf(" name: %s\n value: %s\n -----\n", tools.envp_list->name, tools.envp_list->value);
			tools.envp_list = tools.envp_list->next;
		}*/
/*		while (*tools.envp != NULL)
			printf("--> %s\n", *tools.envp++);*/
		cmd_faker(&tools, line);
		execute(&tools);
	//	add_history(line);
		free(line);
		free_tools(&tools);	
	}
//	clear_history();
	free_arr(tools.envp);
	free_arr(tools.path);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:38:25 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/25 17:56:30 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tools_init(t_tools *tools, char **envp)
{
	tools->envp = ft_arrdup(envp);
	tools->str = NULL;
	tools->envp_list = NULL;
	tools->lexer_list = NULL;
	tools->path = get_path_env(envp);
	tools->exit_code = 0;
	ft_signals(PROCESS_OFF, &tools->exit_code);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	char 	*line;
//	t_envp	*original_envp;

	(void)argv;
	if (argc > 1)
		return (1);
	tools_init(&tools, envp);
	rl_catch_signals = 0;
	while (1)
	{
		line = readline("\033[0;32mminishell$ \033[0m");
		if (!line)
		{
		//	write(1, "\bexit\n", 6);
			printf("\b\b\b\bexit \n");
			break ;
		}
		add_history(line);
		if (!count_quotes(line))
		{
			write(0, "error: unclosed quotes\n", 23);
			free(line);
			continue ;
		}
	//	printf("line %d: %s\n", i, line);
		lexer_token(&tools, line);
		if (!envp_reader(&tools))
			ft_error("bad envp_reader", errno);
/*		while (tools.lexer_list != NULL)
		{
			printf("type: %d\n str: %s\n indx: %d\n ----\n", tools.lexer_list->type, tools.lexer_list->str, tools.lexer_list->indx);

//			printf("\npointer: %p\n", tools.lexer_list);	//lexer_list da leaks de memoria
			tools.lexer_list = tools.lexer_list->next;
		}*/
/*		original_envp = tools.envp_list;
		while (tools.envp_list != NULL)
		{
			printf(" name: %s\n value: %s\n -----\n", tools.envp_list->name, tools.envp_list->value);
			tools.envp_list = tools.envp_list->next;
		}
		tools.envp_list = original_envp;*/
/*		while (*tools.envp != NULL)
			printf("--> %s\n", *tools.envp++);*/
		cmd_faker(&tools, line);
		ft_heredoc(tools.cmd);
	//	print_cdm_list(tools.cmd);
		execute(&tools);
		free(line);
		free_tools(&tools);
		printf("exit_code %d\n", tools.exit_code);
	}
//	clear_history();
	free_arr(tools.envp);
	if (tools.path)
		free_arr(tools.path);
	return (tools.exit_code);
}

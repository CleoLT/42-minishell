/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:38:25 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/08 18:58:30 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tools_init(t_tools *tools, char **envp)
{
	tools->envp = ft_arrdup(envp);
	tools->str = NULL;
	tools->envp_list = NULL;
	tools->lexer_list = NULL;
	tools->exit_code = 0;
	if (!envp_reader(tools))
		ft_error("bad envp_reader", errno);
	delete_env(&tools->envp_list, "OLDPWD");
	envp_addnode("OLDPWD", NULL, &tools->envp_list);
//	exec_export(ft_strdup("OLDPWD"), NULL, NAME_ONLY, &tools->envp_list);
	rl_catch_signals = 0;
	ft_signals(PROCESS_OFF);
	return (1);
}

void	init_tools_loop(t_tools *tools)
{
		tools->path = get_path(*tools);
		tools->built_type = 0;
		signal_exit_code = 0;
}

void	free_tools(t_tools *tools)
{
	free_arr(tools->envp);
	free_envp(&tools->envp_list);
	free_arr(tools->path);
}


int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	char 	*line;

	if (argc > 1)
		print_error(argv[1], ": minishell don't accept any argument", 1);
		//		return (perr_built("", argv[1], 1));
	tools_init(&tools, envp);
	while (1)
	{
		init_tools_loop(&tools);
		line = readline("\033[0;32mminishell$ \033[0m");
		if (!line)
		{
			write(2, "exit\n", 6);
			break ;
		}
		add_history(line);
		if (!count_quotes(line))
		{
			write(0, "error: unclosed quotes\n", 23);
			free(line);
			continue ;
		}
		lexer_token(&tools, line);
	//	if (!envp_reader(&tools))
	//		ft_error("bad envp_reader", errno);
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
		if (tools.cmd && tools.cmd->arg[0])
			tools.built_type = ft_is_builtin(tools.cmd->arg[0]);
		if (!tools.cmd->next && tools.built_type)
			exec_simple_built(&tools, tools.built_type, tools.cmd);
		else
			execute(&tools);
		delete_env(&tools.envp_list, "_");
		free_tools_loop(&tools, line);
		if (signal_exit_code)
			tools.exit_code = signal_exit_code;
		printf("exit_code %d\n", tools.exit_code);
		}
//	clear_history();
	free_tools(&tools);
	return (tools.exit_code);
}

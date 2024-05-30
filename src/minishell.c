/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:38:25 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/30 16:54:23 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_readline(char **line, int	*exit_code)
{
	*line = readline("\033[0;32mminishell$ \033[0m");
		if (signal_exit_code)
			*exit_code = signal_exit_code; //en caso de ctrl + C y ctrl+D
		if (!(*line))
		{
	//		write(2, "exit\n", 6);
	//		break ;
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);
  		  	exit(*exit_code);
		}
		add_history(*line);
}

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	char 	*line;

	if (argc > 1)
		print_error(argv[1], ": minishell don't accept any argument", 1);
	tools_init(&tools, envp);
	while (1)
	{
		init_tools_loop(&tools);
		init_readline(&line, &tools.exit_code);
		if (!count_quotes(line))
		{
			write(2, "error: unclosed quotes\n", 23);
			free(line);
			continue ;
		}
		lexer_token(&tools, line);
	//	print_lexer_list(tools.lexer_list);
		if (ft_parser(&tools) || ft_heredoc(tools.cmd, &tools.exit_code) > 0)
		{
			free_tools_loop(&tools, line);
			continue ;
		}		
		if (tools.cmd && tools.cmd->arg[0])
			tools.built_type = ft_is_builtin(tools.cmd->arg[0]);
		if (!tools.cmd->next && tools.built_type)
			exec_simple_built(&tools, tools.built_type, tools.cmd);
		else
			execute(&tools);
		free_tools_loop(&tools, line);
		}
	free_tools(&tools);
	return (tools.exit_code);
}

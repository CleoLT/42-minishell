/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:38:25 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/31 15:09:43 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_readline(char **line, int	*exit_code)
{
	*line = readline("\033[0;32mminishell$ \033[0m");
	if (g_exit_code)
		*exit_code = g_exit_code;
	if (!(*line))
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		exit(*exit_code);
	}
	add_history(*line);
}

int	quotes(char *line, int *exit_code)
{
	if (!count_quotes(line))
	{
		write(2, "error: unclosed quotes\n", 23);
		free(line);
		*exit_code = 1;
		return (1);
	}
	return (0);
}

void	executor(t_tools *tools)
{
	if (tools->cmd && tools->cmd->arg[0])
		tools->built_type = ft_is_builtin(tools->cmd->arg[0]);
	if (!tools->cmd->next && tools->built_type)
		exec_simple_built(tools, tools->built_type, tools->cmd);
	else
	{
		ft_signals(PROCESS_ON);
		tools->exit_code = 0;
		execute(tools);
		redirect_stdin_out(tools);
		ft_signals(PROCESS_OFF);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	char	*line;

	if (argc > 1)
		print_error(argv[1], ": minishell don't accept any argument", 1);
	tools_init(&tools, envp);
	while (1)
	{
		init_tools_loop(&tools);
		init_readline(&line, &tools.exit_code);
		if (quotes(line, &tools.exit_code))
			continue ;
		lexer_token(&tools, line);
		if (ft_parser(&tools) || ft_heredoc(tools.cmd, &tools.exit_code) > 0)
		{
			free_tools_loop(&tools, line);
			continue ;
		}
		executor(&tools);
		free_tools_loop(&tools, line);
	}
	free_tools(&tools);
	return (tools.exit_code);
}

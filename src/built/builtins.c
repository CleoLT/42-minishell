/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:10:23 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/31 12:47:29 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char *arg)
{
	if (!ft_strncmp(arg, "pwd", 4))
		return (PWD);
	if (!ft_strncmp(arg, "echo", 5))
		return (ECHO);
	if (!ft_strncmp(arg, "cd", 3))
		return (CD);
	if (!ft_strncmp(arg, "export", 7))
		return (EXPORT);
	if (!ft_strncmp(arg, "unset", 6))
		return (UNSET);
	if (!ft_strncmp(arg, "env", 4))
		return (ENV);
	if (!ft_strncmp(arg, "exit", 5))
		return (EXIT);
	return (0);
}

int	exec_built(t_tools *tools, int type, t_cmd *cmd)
{
	if (type == ECHO)
		tools->exit_code = ft_echo(cmd->arg);
	if (type == PWD)
		tools->exit_code = ft_pwd();
	if (type == CD)
		tools->exit_code = ft_cd(cmd->arg, tools);
	if (type == ENV && !cmd->arg[1])
		tools->exit_code = ft_env(tools->envp_list);
	else if (type == ENV && cmd->arg[1])
		write(2, "error: env don't accept any argument\n", 38);
	if (type == UNSET)
		tools->exit_code = ft_unset(&tools->envp_list, cmd->arg);
	if (type == EXPORT)
		tools->exit_code = ft_export(&tools->envp_list, cmd->arg);
	if (type == EXIT)
		ft_exit(cmd->arg, &tools->exit_code);
	return (tools->exit_code);
}

void	exec_simple_built(t_tools *tools, int built_type, t_cmd *cmd)
{
	if (redirect_built(cmd->infile, cmd->outfile) == 1)
	{
		tools->exit_code = 1;
		return ;
	}
	exec_built(tools, built_type, cmd);
	if (cmd->infile)
	{
		dup2(tools->stdin_fd, STDIN_FILENO);
		close(tools->stdin_fd);
	}
	if (cmd->outfile)
	{
		dup2(tools->stdout_fd, STDOUT_FILENO);
		close(tools->stdout_fd);
	}
}

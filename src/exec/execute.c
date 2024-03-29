/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:37:56 by cle-tron          #+#    #+#             */
/*   Updated: 2024/03/29 14:33:39 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(t_tools *tools)
{
	char	*path;
	char	*cmd_path;
	int		i;

	cmd_path = ft_strjoin("/", tools->cmd->arg[0]);
	i = 0;
	while (tools->envp[i])
	{
		path = ft_strjoin(tools->path[i], cmd_path);
		if (access(path, F_OK) == 0)
		{
			free(cmd_path);
			return (path);
		}
		free(path);
		i++;
	}
	free(cmd_path);
	return (NULL);
}


void	exec_cmd(t_tools *tools)
{
	
	char	*path;

	path = find_path(tools);
	printf("path: %s\n", path);
	free(path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:37:56 by cle-tron          #+#    #+#             */
/*   Updated: 2024/03/31 14:09:17 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(t_tools *tools)
{
	char	*path;
	char	*cmd_path;
	int		i;

//	if (tools->cmd->arg[0] == NULL || tools->cmd->arg[0][0] == '\0')
//		return (NULL);
	cmd_path = ft_strjoin("/", tools->cmd->arg[0]);
	i = 0;
	while (tools->path[i])
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
//	int		error;
	if (tools->cmd->arg[0] == NULL || tools->cmd->arg[0][0] == '\0')
		return ;
	path = find_path(tools);
	if (!path)
	{
//		error = ft_strerror(errno);
//		printf("%d\n", error);
//		perror(tools->cmd->arg[0]);
	//	write(2, "bamerror", 7);
		exit(127);
		return ;
	}
//	write(2, "bambo\n", 7);	
	if (execve(path, tools->cmd->arg, tools->envp) != 0)
		ft_error("execve function", errno);
	printf("path: %s\n", path);
	free(path);
}

void	ft_fork(t_tools *tools, int *pipe_fd)
{
//	int		pipe_fd[2];
	pid_t	pid;

	
	pid = fork();
	if (pid == -1)
		ft_error("fork function", errno);
	if (pid == 0)
	{
/*		if (tools->cmd->prev)
		{
			dup2(fd_in, STDIN_FILENO);	
			close(fd_in);
		}
*/		if (tools->cmd->fd_in >= 0)
		{
			dup2(tools->cmd->fd_in, STDIN_FILENO);	
			close(tools->cmd->fd_in);
		}	
		close(pipe_fd[READ_END]);
		if (tools->cmd->next)
		{
			if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
				ft_error("dup2 function", errno);
		}
		close(pipe_fd[WRITE_END]);
		exec_cmd(tools);
	}
	else
	{
		close(pipe_fd[WRITE_END]);
		if (tools->cmd->prev)
		{
		//	close(fd_in);	
			close(tools->cmd->fd_in);
		}
	//	fd_in = pipe_fd[READ_END];
		if (tools->cmd->next)
			tools->cmd->next->fd_in = pipe_fd[READ_END];
		wait(NULL);
	
	}

}

void	execute(t_tools *tools)
{
	int	pipe_fd[2];
//	int	fd_in = 0;
	
	while (tools->cmd)
	{
		if (tools->cmd->next)
			pipe(pipe_fd);
		ft_fork(tools, pipe_fd);
		//	printf("%s | ", tools->cmd->arg[0]);
		tools->cmd = tools->cmd->next;
	}
		wait(NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:37:56 by cle-tron          #+#    #+#             */
/*   Updated: 2024/03/30 19:19:48 by cle-tron         ###   ########.fr       */
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
	int		error;
	if (tools->cmd->arg[0] == NULL || tools->cmd->arg[0][0] == '\0')
		return ;
	path = find_path(tools);
	if (!path)
	{
		error = ft_strerror(errno);
		printf("%d\n", error);
		perror(tools->cmd->arg[0]);
	//	write(2, "bamerror", 7);
		return ;
	}
//	write(2, "bambo\n", 7);	
	if (execve(path, tools->cmd->arg, tools->envp) != 0)
		ft_error("execve function", errno);
	printf("path: %s\n", path);
	free(path);
}

void	make_pipe(t_tools *tools)
{
	int		pipe_fd[2];
	pid_t	pid;

	
	pid = fork();
	if (pid == -1)
		ft_error("fork function", errno);
	if (tools->cmd->next)
	{
		if (pipe(pipe_fd) == -1)
			ft_error("pipe function", errno);
	}
	if (pid == 0)
	{
	//	write(2, "bambino\n", 8);	
		if (tools->cmd->next)
		{
			close(pipe_fd[READ_END]);
			if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
				ft_error("dup2 function", errno);
		}
		exec_cmd(tools);
	}
	if (pid > 0)
	{
		if (tools->cmd->next)
		{
			close(pipe_fd[WRITE_END]);
			//printf("hola");
			if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
				ft_error("dup2 function", errno);
		}
		wait(NULL);
	}


}

void	execute(t_tools *tools)
{
	while (tools->cmd)
	{
		make_pipe(tools);
	//	printf("%s | ", tools->cmd->arg[0]);
		tools->cmd = tools->cmd->next;
	}
/*
pid_t test;
test = fork();
int fd[2];
pipe(fd);
if (test == 0)
	exec_cmd(tools);
wait(NULL);*/
}

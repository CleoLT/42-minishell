/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:37:56 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/31 19:06:59 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all(pid_t *pid, t_tools *tools)
{
	int	i;
	int	status;

	i = 0;
	while (i < tools->t_cmd_size)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			tools->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				tools->exit_code = 131;
			if (WTERMSIG(status) == SIGINT)
				tools->exit_code = 130;
		}
		i++;
	}
}

void	exec_cmd(t_tools *tools, t_cmd *cmd)
{
	char	*path;
	int		built_type;

	if (cmd->arg == NULL || cmd->arg[0] == NULL )
		exit(tools->exit_code);
	built_type = ft_is_builtin(cmd->arg[0]);
	if (built_type)
		exit(exec_built(tools, built_type, cmd));
	if (cmd->arg[0][0] == '\0')
		print_error(cmd->arg[0], ": command not found", 127);
	path = find_path(tools, cmd);
	if (!path && access(cmd->arg[0], F_OK) == 0)
	{
		path = ft_strdup(cmd->arg[0]);
		if (ft_strncmp(path, "./", 2) && ft_strncmp(path, "/", 1))
			print_error(cmd->arg[0], ": command not found", 127);
		else if (!(ft_strncmp(path, "./", 2)) && access(cmd->arg[0], X_OK))
			print_error(cmd->arg[0], ": permission denied", 126);
	}
	if (!path)
		print_error(cmd->arg[0], ": command not found", 127);
	if (execve(path, cmd->arg, tools->envp) == -1 && is_directory(cmd->arg[0]))
		print_error(cmd->arg[0], ": is a directory", 126);
	free(path);
}

void	child_process(t_cmd *cmd, t_tools *tools, int *pipe_fd)
{
	int	fd_out;
	int	fd_in;

	if (cmd->infile)
	{
		fd_in = redirect_infile(cmd->infile);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->outfile)
	{
		fd_out = redirect_outfile(cmd->outfile);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (cmd->next)
	{
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipe_fd[WRITE_END]);
	}
	close(pipe_fd[READ_END]);
	exec_cmd(tools, cmd);
}

void	execute(t_tools *tools)
{
	int		pipe_fd[2];
	int		i;
	t_cmd	*cmd;
	pid_t	*pid;

	cmd = tools->cmd;
	pid = malloc(sizeof(pid_t) * tools->t_cmd_size);
	if (!pid)
		return ;
	i = 0;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipe_fd);
		pid[i] = fork();
		if (pid[i] == 0)
			child_process(cmd, tools, pipe_fd);
		dup2(pipe_fd[READ_END], STDIN_FILENO);
		close(pipe_fd[READ_END]);
		close(pipe_fd[WRITE_END]);
		cmd = cmd->next;
		i++;
	}
	wait_all(pid, tools);
	free(pid);
}

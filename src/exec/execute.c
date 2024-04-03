/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:37:56 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/03 18:22:53 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char *arg)
{
	if (!strncmp(arg, "pwd", 4))
		return (PWD);
	if (!strncmp(arg, "echo", 5))
		return (ECHO);
	return (0);
}

char	*find_path(t_tools *tools, t_cmd *cmd)
{
	char	*path;
	char	*cmd_path;
	int		i;

	cmd_path = ft_strjoin("/", cmd->arg[0]);
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

void	exec_cmd(t_tools *tools, t_cmd *cmd)
{
	char	*path;
	int		built_type;
	
	if (cmd->arg[0] == NULL) // esto en realidad no va aqui, va en parser
		print_error(NULL, "syntax error near unexpected token `|'",  127);
	built_type = ft_is_builtin(cmd->arg[0]);
	if (built_type)
		(exec_built(tools, built_type, cmd));
	if (cmd->arg[0][0] == '\0')
		print_error(cmd->arg[0], ": command not found",  127);
	path = find_path(tools, cmd);
	if (!path && access(cmd->arg[0], X_OK) == 0)
		path = ft_strdup(cmd->arg[0]);
	else if (access(cmd->arg[0], F_OK) == 0)
		print_error(cmd->arg[0], ": permission denied",  126);
	if (!path)
		print_error(cmd->arg[0], ": command not found",  127);
	if (execve(path, cmd->arg, tools->envp) != 0)
		ft_error("execve function", errno);
	free(path);
}

void	ft_fork(t_tools *tools, t_cmd *cmd, int *pipe_fd, int fd_in, pid_t pid)
{
//	pid_t	pid[tools->t_cmd_size];
//	static int	i = 0;

	pid = fork();
	if (pid == -1)
		ft_error("fork function", errno);
	if (pid == 0)
	{
		if (cmd->prev)
		{
			dup2(fd_in, STDIN_FILENO);	
			close(fd_in);
		}
	/*	if (tools->cmd->fd_in >= 0)
		{
			dup2(tools->cmd->fd_in, STDIN_FILENO);	
			close(tools->cmd->fd_in);
		}	
	*/	close(pipe_fd[READ_END]);
		if (cmd->next)
		{
			if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
				ft_error("dup2 function", errno);
		}
		close(pipe_fd[WRITE_END]);
		exec_cmd(tools, cmd);
	}
}

void kill_and_wait(pid_t *pid, int size)
{
	int i = 0;
	int	status;

//	while (i < size)
//	{
//		kill(pid[i], SIGKILL);
//		i++;
//	}
//	i = 0;
  while (i < size) // Récupère la sortie de chaque fils
    {
        waitpid(pid[i], &status, 0);
        if (WIFEXITED(status))
            printf("Fils [%d] a terminé normalement.\n", pid[i]);
        else if (WIFSIGNALED(status))
        {
            printf("Fils [%d] a ete interrompu.\n", pid[i]);
            if (WTERMSIG(status) == SIGTERM)
                printf("\e[31mFils [%d] a recu le signal %d, SIGTERM\e[0m\n",
                            pid[i], WTERMSIG(status));
            if (WTERMSIG(status) == SIGKILL)
                printf("\e[31mFils [%d] a recu le signal %d, SIGKILL\e[0m\n",
                            pid[i], WTERMSIG(status));
        }
        i++;
    }


}

void	execute(t_tools *tools)
{
	int	pipe_fd[2];
	int	fd_in = 0;
	t_cmd	*cmd;
	int i = 0;

	cmd = tools->cmd;
	pid_t	pid[tools->t_cmd_size];
	while (cmd)
	{
		if (cmd->next)
			pipe(pipe_fd);
		ft_fork(tools, cmd, pipe_fd, fd_in, pid[i]);
		close(pipe_fd[WRITE_END]);
		if (cmd->prev)
		{
			close(fd_in);	
		//	close(tools->cmd->fd_in);
		}
		if (cmd->next)
		{
			fd_in = pipe_fd[READ_END];
//			tools->cmd->next->fd_in = pipe_fd[READ_END];
		}
		wait(NULL);
		//	kill_and_wait(pid, tools->t_cmd_size);
		if (cmd->next)// truc bizarre sinon readline beugue avec 1 cmd
			cmd = cmd->next;
		else
			break;
		i++;
	}
}

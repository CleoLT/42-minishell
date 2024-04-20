/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:37:56 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/20 13:02:12 by cle-tron         ###   ########.fr       */
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
	return (0);
}


void wait_all(pid_t *pid, t_tools *tools)
{
	int i = 0;
	int	status;
	while (i < tools->t_cmd_size)    
	{
        waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			  tools->exit_code = WEXITSTATUS(status);
			//printf("Fils [%d] a terminé normalement.\n", pid[i]);
		}
        else if (WIFSIGNALED(status))
        {
			//printf("Fils [%d] a ete interrompu.\n", pid[i]);
			if (WTERMSIG(status) == SIGQUIT)
			{
				tools->exit_code = 131;
         //       printf("\e[31mFils [%d] a recu le signal %d, SIGQUIT\e[0m\n",
          //                  pid[i], WTERMSIG(status));
			}
			if (WTERMSIG(status) == SIGINT)
			{
				tools->exit_code = 130;
             //   printf("\e[31mFils [%d] a recu le signal %d, SIGINT\e[0m\n",
               //             pid[i], WTERMSIG(status));
        	}
		}
        i++;
    }


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
	
	if (cmd->arg[0] == NULL)
		exit(tools->exit_code);
	built_type = ft_is_builtin(cmd->arg[0]);
	if (built_type)
	{
		(exec_built(tools, built_type, cmd));
		return ;
	}
	if (cmd->arg[0][0] == '\0')
		print_error(cmd->arg[0], ": command not found", 127);
	path = find_path(tools, cmd);
	if (!path && access(cmd->arg[0], X_OK) == 0)
		path = ft_strdup(cmd->arg[0]);
	else if (access(cmd->arg[0], F_OK) == 0)
		print_error(cmd->arg[0], ": permission denied", 126);
	if (!path)
		print_error(cmd->arg[0], ": command not found", 127);
	if (execve(path, cmd->arg, tools->envp) != 0)
		ft_error("execve function", errno);
	free(path);
}

int	open_infile(char *file)
{
	int	fd;

	if (access(file, F_OK) != 0)
		ft_error(file, 1);
	if (access(file, R_OK) != 0)
		ft_error(file, 1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("open function", errno);
	return (fd);
}

int	heredoc(char *limit)
{
	int	fd;
	char *line;

	fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("open function", errno);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ; 
		if (!ft_strncmp(limit, line, ft_strlen(limit) + 1))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);

	
	fd = open("/tmp/.heredoc", O_RDONLY);
	if (fd == -1)
		ft_error("open function", errno);
	return (fd);

}

void child_process(t_cmd *cmd, t_tools *tools, int *pipe_fd, int fd_in)
{
	if (cmd->heredoc)
		fd_in = heredoc(cmd->heredoc);
//	if (cmd->infile)
//		fd_in = open_infile(cmd->infile);
	if (cmd->prev || cmd->infile || cmd->heredoc)
	{	
		dup2(fd_in, STDIN_FILENO);	
		close(fd_in);
	}
	if (cmd->next)
	{
		close(pipe_fd[READ_END]);
		if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
			ft_error("dup2 function", errno);
		close(pipe_fd[WRITE_END]);
	}
//	if (cmd->next || cmd->prev)
//		close(pipe_fd[WRITE_END]);

//	signal(SIGQUIT, handle_sigquit); 
	exec_cmd(tools, cmd);
}


void	execute(t_tools *tools)
{
	int	pipe_fd[2];
	int	fd_in = 0;
	t_cmd	*cmd;
	int i = 0;

	cmd = tools->cmd;
	pid_t	pid[tools->t_cmd_size];
	ft_signals(PROCESS_ON, &tools->exit_code);

	while (cmd)
	{
		if (cmd->next)
			pipe(pipe_fd);
		pid[i] = fork();
		if (pid[i] == 0)
			child_process(cmd, tools, pipe_fd, fd_in);
//		if (cmd->prev)
//			close(fd_in);
		if (cmd->next)
		{
			fd_in = pipe_fd[READ_END];
			close(pipe_fd[WRITE_END]);
		}
		cmd = cmd->next;
		i++;
	}
	wait_all(pid, tools);
	ft_signals(PROCESS_OFF, &tools->exit_code);
}

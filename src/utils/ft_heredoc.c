/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:22:27 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/31 17:08:14 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	hd_loop(t_tools *tools, char *limiter, int fd)
{
	char	*line;
	char	*newl;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		newl = malloc(sizeof(char *) * expander_newlen(tools, line) + 1);
		expand_str(tools, newl, line);
		if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1))
		{
			free(line);
			break ;
		}
		free(line);
		ft_putendl_fd(newl, fd);
	}
}

void	create_hd_file(char *limiter, char *hd_num, t_tools *tools)
{
	int		fd;
	char	*hd_name;

	ft_signals(PROCESS_HD);
	hd_name = ft_strjoin("/tmp/.heredoc", hd_num);
	fd = open(hd_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("open function", errno);
	hd_loop(tools, limiter, fd);
	close(fd);
	exit(0);
}

void	heredoc_process(int count_hd, char **infile, t_tools *tools)
{
	char	*hd_num;
	pid_t	pid;
	int		status;

	hd_num = ft_itoa(count_hd++);
	pid = fork();
	if (pid == 0)
		create_hd_file(*infile, hd_num, tools);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		tools->exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			tools->exit_code = 1;
	}
	*infile = ft_strjoin("/tmp/.heredoc", hd_num);
	free(hd_num);
}

int	ft_heredoc(t_cmd *cmd, t_tools *tools)
{
	int		i;
	int		count_hd;

	count_hd = 0;
	while (cmd)
	{
		if (cmd->infile)
		{
			i = 0;
			while (cmd->infile[i])
			{
				if (cmd->infile[i][1])
				{
					heredoc_process(count_hd++, &cmd->infile[i][0], tools);
					if (tools->exit_code == 1)
						return (tools->exit_code);
				}
				i++;
			}
		}
		cmd = cmd->next;
	}
	if (count_hd > 0)
		return (tools->exit_code);
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:22:27 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/16 19:38:35 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_hd_file(char *limiter, char *hd_num)
{
	char	*line;
	int		fd;
	char	*hd_name;

	ft_signals(PROCESS_HD);
	hd_name = ft_strjoin("/tmp/.heredoc", hd_num);
	fd = open(hd_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("open function", errno);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ; 
		if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);	
	exit(0);
}

void	heredoc_process(int count_hd, char **infile, int *exit_code)
{
	char	*hd_num;
	pid_t	pid;
	int		status;

	hd_num = ft_itoa(count_hd++);
	pid = fork();
	if (pid == 0)
		create_hd_file(*infile, hd_num);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status); //esto no es del todo cierto
	 if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
	//		*sigint = 1;
			*exit_code = 1;
		//	*sigint = ;
		}
	}	
	*infile = ft_strjoin("/tmp/.heredoc", hd_num);
	free(hd_num);
}

int	ft_heredoc(t_cmd *cmd, int *exit_code)
{
	int		i;
	int		count_hd;
//	int		sigint;

//	sigint = 0;
	count_hd = 0;
	while (cmd)
	{
		if (cmd->infile)
		{
			i = 0;
			while (cmd->infile[i])
			{
				if (cmd->infile[i][1])
					heredoc_process(count_hd++, &cmd->infile[i][0], exit_code);
				i++;
			}
		}
	cmd = cmd->next;
	}
	printf("%d\n", *exit_code);
	if (count_hd > 0)
		return (*exit_code);
	return (-1);
}



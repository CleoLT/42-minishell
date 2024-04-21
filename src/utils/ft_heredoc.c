/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:22:27 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/21 16:43:56 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*create_hd_file(char *limiter, int hd)
{
	char	*line;
	int		fd;
	char	*hd_name;
	char	*num;

	num = ft_itoa(hd);
	hd_name = ft_strjoin("/tmp/.heredoc", num);
	free(num);
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
	return (hd_name);
}

void	ft_heredoc(t_cmd *cmd)
{
	int i;
	int	count_hd;
	char *hd_name;

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
					hd_name = create_hd_file(cmd->infile[i][0], count_hd++);
					cmd->infile[i][0] = hd_name;
				}
				i++;
			}
		}
	cmd = cmd->next;
	}
}



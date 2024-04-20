/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_infile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:13:12 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/20 16:53:04 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);	
	fd = open("/tmp/.heredoc", O_RDONLY);
	if (fd == -1)
		ft_error("open function", errno);
	return (fd);
}

int	close_fds(char *heredoc, int fd_infile, int fd_heredoc)
{
	if (heredoc)
	{
		if (fd_infile > 0)
			close(fd_infile);	
		return (fd_heredoc);
	}
	else 
	{
		if (fd_heredoc > 0)
			close(fd_heredoc);
		return (fd_infile);
	}
}

int	redirect_infile(char ***infile)
{
	int i;
	int	fd_heredoc;
	int fd_infile;

	i = 0;
	while (infile[i])
	{
		if (infile[i][1])
			fd_heredoc = heredoc(infile[i][0]);
		if (infile[++i] && fd_heredoc > 0)
			close(fd_heredoc);
		unlink("/tmp/.heredoc");
	}
	i = 0;
	while (infile[i])
	{
		if (!infile[i][1])
			fd_infile = open_infile(infile[i][0]);
		if (infile[++i] && fd_infile > 0)
			close(fd_infile);
	}
	return (close_fds(infile[i - 1][1], fd_infile, fd_heredoc));
}

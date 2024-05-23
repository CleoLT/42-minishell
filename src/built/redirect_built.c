/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_built.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:13:12 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/23 17:02:16 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	open_infileb(char *file)
{
	int	fd;

	if (access(file, F_OK) != 0)
		return (perr_built("", file, -1));
	if (access(file, R_OK) != 0)
		return (perr_built("", file, -1));
	fd = open(file, O_RDONLY);
//	if (fd == -1)
//		ft_error("open function", errno);
	return (fd);
}

static int	open_outfileb(char **file)
{
	int	fd;
	struct stat sb;

	stat(*file, &sb);
	if (S_ISDIR(sb.st_mode))
		return (err_built(*file, "", "Is a directory", -1));
	if (file[1])
		fd = open(*file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(*file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(*file, W_OK) != 0)
		return (perr_built("", *file, -1));
	if (fd == -1)
		return (perr_built("", *file, -1));
	return (fd);
}

int	redirect_infileb(char ***infile)
{
	int i;
	int fd;

	i = 0;

	while (infile[i])
	{
		fd = open_infileb(infile[i][0]);
		if (fd == -1)
			return (-1);
		if (infile[i + 1] && fd > 0)
			close(fd);
		if (infile[i][1]) //if heredoc
			unlink(infile[i][0]);
		i++;
	}
	return (fd);
}

int	redirect_outfileb(char ***outfile)
{
	int	i;
	int	fd;

	i = 0;
	while (outfile[i])
	{
		fd = open_outfileb(outfile[i]);
		if (fd == -1)
			return (-1);
		if (outfile[++i] && fd > 0)
			close(fd);
	}
	return (fd);
}

int	redirect_built(char ***infile, char ***outfile)
{
	int fd_in;
	int	fd_out;

	if (infile)
	{
		fd_in = redirect_infileb(infile);
		if (fd_in == -1)
			return (1);
		dup2(fd_in, STDIN_FILENO);	
		close(fd_in);	
	}
	if (outfile)
	{
		fd_out = redirect_outfileb(outfile);
		if (fd_out == -1)
			return (1);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	return (0);
}

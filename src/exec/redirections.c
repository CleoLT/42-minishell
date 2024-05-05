/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:13:12 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/05 12:13:02 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	open_infile(char *file)
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

static int	open_outfile(char **file)
{
	int	fd;

	if (file[1])
		fd = open(*file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(*file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(*file, W_OK) != 0)
		ft_error(*file, 1);
	if (fd == -1)
		ft_error(*file, 1);
	return (fd);
}

int	redirect_infile(char ***infile)
{
	int i;
	int fd;

	i = 0;

	while (infile[i])
	{
		fd = open_infile(infile[i][0]);
		if (infile[i + 1] && fd > 0)
			close(fd);
		if (infile[i][1]) //if heredoc
			unlink(infile[i][0]);
		i++;
	}
	return (fd);
}

int	redirect_outfile(char ***outfile)
{
	int	i;
	int	fd;

	i = 0;
	while (outfile[i])
	{
		fd = open_outfile(outfile[i]);
		if (outfile[++i] && fd > 0)
			close(fd);
	}
	return (fd);
}

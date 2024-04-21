/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_infile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:13:12 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/21 16:51:13 by cle-tron         ###   ########.fr       */
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

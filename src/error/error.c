/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:36:04 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/18 18:20:19 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *arg, int exit_code)
{
	perror(arg);
	exit(exit_code);
}

void	ft_error_built(char *cmd, char *arg, int exit_code)
{
	ft_putstr_fd(cmd, 2);
	perror(arg);
	exit(exit_code);
}

void	print_error(char *cmd, char *str, int exit_code)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(str, 2);
	exit(exit_code);
}

int	ft_strerror(int exit_code)
{
	ft_putendl_fd(strerror(exit_code), STDERR_FILENO);
	return(exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:36:04 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/04 21:24:43 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *arg, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (!arg[0])
		write(STDERR_FILENO, " : ", 3);
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
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(str, 2);
	exit(exit_code);
}

int	ft_strerror(int exit_code)
{	
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(strerror(exit_code), STDERR_FILENO);
	return(exit_code);
}


int	err_built(char *cmd, char *arg, char *error, int error_num)
{
	
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	return (error_num);
}



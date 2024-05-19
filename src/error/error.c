/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:36:04 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/18 15:48:36 by cle-tron         ###   ########.fr       */
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


int	err_built(char *cmd, char *arg, char *error, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	return (exit_code);
}

int	perr_built(char *cmd, char *arg, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, 2);
	perror(arg);
	return (exit_code);
}

int	err_syntax(int type)
{
	char	*token;

	if (type == PIPE)
		token = "|";
	else if (type == INPUT)
		token = "<";
	else if (type == OUTPUT)
		token = ">";
	else if (type == HEREDOC)
		token = "<<";
	else if (type == HEREDOC)
		token = ">>";
	else
		token = "newline";
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", STDERR_FILENO);
	return (1);
}


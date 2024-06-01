/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:36:04 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/01 11:41:15 by irozhkov         ###   ########.fr       */
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

void	malloc_error(void)
{
	ft_putstr_fd("minishell: error malloc function", STDERR_FILENO);
}

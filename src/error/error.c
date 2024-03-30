/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:36:04 by cle-tron          #+#    #+#             */
/*   Updated: 2024/03/30 15:30:14 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *arg, int exit_code)
{
	perror(arg);
	exit(exit_code);
}

int	ft_strerror(int exit_code)
{
	ft_putendl_fd(strerror(exit_code), STDERR_FILENO);
	return(exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:48:38 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/03 19:24:20 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals(void)
{
	signal(SIGQUIT, handle_sigquit);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	ft_putstr_fd("exit\n", STDIN_FILENO);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:48:38 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/09 14:53:28 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay(); // poner condition si un command se esta ejecutando
}

void	handle_sigquit(int sig)
{
		printf("Quit: %d\n", sig);		
}

void	signals(void)
{
	signal(SIGQUIT, SIG_IGN);
//	signal(SIGQUIT, handle_sigquit);   // ctrl + '\' llamar si hay un process en curso
	signal(SIGINT, handle_sigint); // ctrl + C
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:48:38 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/18 16:33:12 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_process(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
//	signal(SIGINT, handle_sigint_process);
}

void	handle_sigquit(int sig)
{
		printf("Quit: %d\n", sig);		
}

void	ft_signals(int process, int *exit_code)
{
	if (process == PROCESS_OFF)
	{
		signal(SIGQUIT, SIG_IGN);
	//	sigaction()
		if (!signal(SIGINT, handle_sigint))
		{
	   		*exit_code = 1;			// ctrl + C   ///esta mierda no funciona!!!
			write(2, "hono\n", 5);
		}
	}
	else if (process == PROCESS_ON)
	{
		signal(SIGQUIT, handle_sigquit);   // ctrl + '\' llamar si hay un process en curso
		signal(SIGINT, handle_sigint_process); //ctrl + C in child porcess
	}
}

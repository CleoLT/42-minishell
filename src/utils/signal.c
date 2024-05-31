/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:48:38 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/31 15:10:14 by cle-tron         ###   ########.fr       */
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
	g_exit_code = 1;
}

void	handle_sigint_process(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
}

void	handle_sigquit(int sig)
{
	printf("Quit: %d\n", sig);
}

void	handle_sigint_heredoc(int sig)
{
	struct termios	term_attr;

	(void)sig;
	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &term_attr) != -1)
		{
			term_attr.c_lflag |= ECHO;
			tcsetattr(STDIN_FILENO, TCSANOW, &term_attr);
		}
	}
	exit(1);
}

void	ft_signals(int process)
{
	if (process == PROCESS_OFF)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
	}
	else if (process == PROCESS_ON)
	{
		signal(SIGQUIT, handle_sigquit);
		signal(SIGINT, handle_sigint_process);
	}
	else if (process == PROCESS_HD)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint_heredoc);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:10:23 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/03 18:21:30 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[MAXPATHLEN];

	write(2, "hola", 4);
	if (getcwd(cwd, MAXPATHLEN))
		printf("%s\n", cwd);
	else 
		ft_error("getcwd function", errno);
}

void	ft_echo(char **arg)
{
	int	nl_option;
	int i = 0;
	int	size;

	size = array_len(arg);
	nl_option = 0;
	if (!strncmp(arg[1], "-n", 3))
		nl_option = 1;
	i = nl_option + 1;
	while (arg[i])
	{
		printf("%s", arg[i++]);
		if (i < size)
			printf(" ");
	}
	if (!nl_option)
		printf("\n");
}

void	exec_built(t_tools *tools, int type, t_cmd *cmd)
{
	printf("%s\n", tools->cmd->arg[0]);
	if (type == ECHO)
		ft_echo(cmd->arg);
	if (type == PWD)
		ft_pwd();
	exit(EXIT_SUCCESS);
}

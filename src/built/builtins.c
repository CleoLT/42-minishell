/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:10:23 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/24 15:15:35 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[MAXPATHLEN];

	if (getcwd(cwd, MAXPATHLEN))
		printf("%s\n", cwd);
	else 
		ft_error("getcwd function", errno);
}

void	ft_echo(char **arg)
{
	int	nl_option;
	int i;
	int j;
	int	size;

	i = 0;
	size = array_len(arg);
	nl_option = 0;
	while (arg[++i] && arg[i][0] == '-' && arg[i][1] == 'n')
	{
		j = 2;
		while (arg[i][j] == 'n')
			j++;
		if (arg[i][j] != '\0')		
			break ;
		nl_option++;
	}
	while (arg[i])
	{
		printf("%s", arg[i++]);
		if (i < size)
			printf(" ");
	}
	if (!nl_option)
		printf("\n");
}

void	ft_env(t_envp *env)
{

	while (env)
	{
		if (env->name)
			printf("%s=", env->name);
		if (env->value)
			printf("%s\n", env->value);
		env = env->next;
	}	

}

void	exec_built(t_tools *tools, int type, t_cmd *cmd)
{
	if (type == ECHO)
		ft_echo(cmd->arg);
	if (type == PWD)
		ft_pwd();
	if (type == CD)
		ft_cd(cmd->arg, tools); 
	if (type == ENV)
		ft_env(tools->envp_list);
	exit(EXIT_SUCCESS);
}

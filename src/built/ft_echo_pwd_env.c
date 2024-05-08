/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_pwd_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:36 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/08 17:05:43 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	cwd[MAXPATHLEN];

	if (getcwd(cwd, MAXPATHLEN))
		printf("%s\n", cwd);
	else 
		ft_error("getcwd function", errno);
	return (EXIT_SUCCESS);
}

int	ft_echo(char **arg)
{
	int	nl_option;
	int i;
	int j;

	i = 0;
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
		if (arg[i])
			printf(" ");
	}
	if (!nl_option)
		printf("\n");
	return (EXIT_SUCCESS);
}

int	ft_env(t_envp *env)
{
	while (env)
	{
		if (env->name && env->value && strncmp(env->name, "_", 2))
		{	
			printf("%s=", env->name);
			printf("%s\n", env->value);
		}
		env = env->next;
	}	
	printf("_=/usr/bin/env\n");
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:10:23 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/04 16:50:55 by cle-tron         ###   ########.fr       */
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
		if (i < size) // essayer arg[i + 1] pour avoir que 25 lignes
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

void print_env_rev(t_envp *env)
{
	printf("\n");
	while (env->next)
		env = env->next;
	while (env)
	{
		if (env->name)
			printf("%s=", env->name);
		if (env->value)
			printf("%s\n", env->value);
		env = env->prev;
	}

}

int	ft_is_builtin(char *arg)
{
	if (!ft_strncmp(arg, "pwd", 4))
		return (PWD);
	if (!ft_strncmp(arg, "echo", 5))
		return (ECHO);
	if (!ft_strncmp(arg, "cd", 3))
		return (CD);
	if (!ft_strncmp(arg, "export", 7))
		return (EXPORT);
	if (!ft_strncmp(arg, "unset", 6))
		return (UNSET);
	if (!ft_strncmp(arg, "env", 4))
		return (ENV);
	if (!ft_strncmp(arg, "exit", 5))
		return (EXIT);
	return (0);
}

int	exec_built(t_tools *tools, int type, t_cmd *cmd)
{

	if (type == ECHO)
		tools->exit_code = ft_echo(cmd->arg);
	if (type == PWD)
		tools->exit_code = ft_pwd();
//	if (type == CD)
//		ft_cd(cmd->arg, tools); 
	if (type == ENV && !cmd->arg[1])
		tools->exit_code = ft_env(tools->envp_list);
	else if (type == ENV && cmd->arg[1])
		write(2, "error: env don't accept any argument\n", 38);
	if (type == UNSET)
		tools->exit_code = ft_unset(&tools->envp_list, cmd->arg);
	if (type == EXPORT)
		tools->exit_code = ft_export(&tools->envp_list, cmd->arg);
	if (type == EXIT)
		ft_exit(cmd->arg, &tools->exit_code);
	return (tools->exit_code);
}

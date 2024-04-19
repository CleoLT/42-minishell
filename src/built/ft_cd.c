/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:01:41 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/19 15:13:15 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_value(char *name, t_envp *env)
{
	char *value;

	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(env->name)))
		{
			value = ft_strdup(env->value);
			return (value);
		}
		env = env->next;
	}
//	ft_putstr_fd("cd: ", 2);
//	print_error(name, " not set", 1);
	return (NULL);
}

void	replace_env_value(char *name, char *value, t_envp *env)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(env->name)))
		{
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}

void	ft_cd(char **arg, t_tools *tools)
{
	char	*path;

	if (arg[1] == NULL || !ft_strncmp(arg[1], "~", 2)) 
	{
		path = find_env_value("HOME", tools->envp_list);
		printf("%s\n", path);
		if (!path)
			print_error("cd: ", "HOME not set", 1);
	}
	else if (!ft_strncmp(arg[1], "-", 2))
	{
		path = find_env_value("OLDPWD", tools->envp_list);
		if (!path)
			print_error("cd: ", "OLDPWD not set", 1);
		printf("%s\n", path);
	}
	else 
		path = ft_strdup(arg[1]);
	if (chdir(path))
		ft_error_built("cd: ", path, 1);
//	replace_env_value("OLDPWD", getcwd(cwd, MAXPATHLEN)
	replace_env_value("PWD", path, tools->envp_list);

	free(path);
}

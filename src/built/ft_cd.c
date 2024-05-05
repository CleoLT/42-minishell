/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:01:41 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/05 18:47:05 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_value(char *name, t_envp *env)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(env->name)))
		{
			if (env->value)
				return (ft_strdup(env->value));
			else 
				return  (NULL);
		}
		env = env->next;
	}
	return (NULL);
}

void	replace_env_value(char *name, char *value, t_envp *env)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(env->name)))
		{
			if (env->value)
				free(env->value);
			if (!value)
				value = "";
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}

int	err_env_notset(char *cmd, char *env, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(env, STDERR_FILENO);
	ft_putendl_fd(" not set", STDERR_FILENO);
	return (exit_code);

}

int	ft_cd(char **arg, t_tools *tools)
{
	char	*path;

	tools->exit_code = EXIT_SUCCESS;
	if (!arg[1] || !ft_strncmp(arg[1], "~", 2)) 
	{
		path = find_env_value("HOME", tools->envp_list);
		if (!path)
		{
			if (arg[1] && !ft_strncmp(arg[1], "~", 2)) 
				path = ft_strdup(getenv("HOME"));
			else
			{
			tools->exit_code = err_env_notset(arg[0], "HOME", 1);
			return (tools->exit_code);
			}
		}
	}
		else if (!ft_strncmp(arg[1], "-", 2))
	{
	
		path = find_env_value("OLDPWD", tools->envp_list);
		if (!path)
		{
			tools->exit_code = err_env_notset(arg[0], "OLDPWD", 1);
			return (tools->exit_code);
		}
		printf("%s\n", getenv("OLDPWD")); //??????????????
	}
	else 
		path = ft_strdup(arg[1]);
	//	printf("%s\n", path);
	if (chdir(path))
		tools->exit_code = perr_built("cd: ", path, 1);
	free(path);

	char *oldpwd = find_env_value("PWD", tools->envp_list);
	replace_env_value("OLDPWD", oldpwd, tools->envp_list);
	free(oldpwd);

	char	cwd[MAXPATHLEN];
	if (getcwd(cwd, MAXPATHLEN))
		replace_env_value("PWD", cwd, tools->envp_list);
	
	return (tools->exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:01:41 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/22 16:15:02 by cle-tron         ###   ########.fr       */
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

/*
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
}*/

int	err_env_notset(char *cmd, char *env, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(env, STDERR_FILENO);
	ft_putendl_fd(" not set", STDERR_FILENO);
	return (exit_code);
}

char	*home_and_oldpwd_path(char **arg, int *exit_code, t_envp *envp_list)
{
	char	*path;

	path = NULL;
	if (!arg[1] || !ft_strncmp(arg[1], "~", 2)) 
	{
		path = find_env_value("HOME", envp_list);
		if (!path)
		{
			if (arg[1] && !ft_strncmp(arg[1], "~", 2)) 
				path = ft_strdup(getenv("HOME"));
			else
				*exit_code = err_env_notset(arg[0], "HOME", 1);
		}
	}
	else if (!ft_strncmp(arg[1], "-", 2))
	{
		path = find_env_value("OLDPWD", envp_list);
		if (!path)
			*exit_code = err_env_notset(arg[0], "OLDPWD", 1);
	}
	return (path);
}


int	ft_cd(char **arg, t_tools *tools)
{
	char	*path;
	char	*oldpwd;
	char	cwd[MAXPATHLEN];

	tools->exit_code = EXIT_SUCCESS;
	path = home_and_oldpwd_path(arg, &tools->exit_code, tools->envp_list);
	if (tools->exit_code)
		return (tools->exit_code);	
	else if (!path) 
		path = ft_strdup(arg[1]);
	if (chdir(path) && path[0] != '\0')
		tools->exit_code = perr_built("cd: ", path, 1);
	free(path);
	oldpwd = find_env_value("PWD", tools->envp_list);
	if (!oldpwd)
		oldpwd = ft_strdup("");
	exec_export(ft_strdup("OLDPWD"), oldpwd, REPLACE_MODE, &tools->envp_list);
	if (getcwd(cwd, MAXPATHLEN))
		exec_export(ft_strdup("PWD"), ft_strdup(cwd), REPLACE_MODE, \
			   											&tools->envp_list);
	return (tools->exit_code);
}

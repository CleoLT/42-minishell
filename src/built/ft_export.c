/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:23:48 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/31 13:03:42 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_values(char *arg, char **name, char **value, int *mode)
{
	int	i;

	i = -1;
	*mode = NAME_ONLY;
	while (arg[++i])
	{
		if (arg[i] == '=')
		{
			*mode = REPLACE_MODE;
			if (arg[i - 1] == '+')
				*mode = APPEND_MODE;
			break ;
		}
	}
	if (*mode == NAME_ONLY)
		*value = NULL;
	else
		*value = ft_substr(arg, i + 1, ft_strlen(arg));
	if (*mode == APPEND_MODE)
		*name = ft_substr(arg, 0, i - 1);
	else
		*name = ft_substr(arg, 0, i);
}

int	check_name_error(char *arg, char **name, char **value, int *exit_code)
{
	int	i;

	i = -1;
	while ((*name)[++i])
	{
		if ((*name)[i] != '_' && !(ft_isalnum((*name)[i])))
		{
			free(*name);
			free(*value);
			*exit_code = print_error_unset("export", arg);
			return (1);
		}
	}
	if (!(ft_strncmp(*name, "_", 2)))
		return (1);
	return (EXIT_SUCCESS);
}

void	replace_value(char *name, char *value, int mode, t_envp **env)
{
	char	*tmp_value;

	if (mode == NAME_ONLY)
		free(value);
	else if (mode == APPEND_MODE)
	{
		tmp_value = ft_strjoin((*env)->value, value);
		free((*env)->value);
		(*env)->value = tmp_value;
		free(value);
	}
	else if (mode == REPLACE_MODE)
	{
		free((*env)->value);
		(*env)->value = value;
	}
	free(name);
}

void	exec_export(char *name, char *value, int mode, t_envp **envp)
{
	t_envp	*env;

	env = *envp;
	while (env)
	{
		if (!strncmp(env->name, name, ft_strlen(name) + 1))
			return (replace_value(name, value, mode, &env));
		env = env->next;
	}
	envp_addnode(name, value, envp);
	free(name);
	free(value);
}

int	ft_export(t_envp **envp, char **arg)
{
	int		exit_code;
	int		i;
	char	*name;
	char	*value;
	int		mode;

	name = NULL;
	value = NULL;
	exit_code = EXIT_SUCCESS;
	i = 0;
	if (!arg[1])
		return (print_export(*envp));
	while (arg[++i])
	{
		if (arg[i][0] != '_' && !(ft_isalpha(arg[i][0])))
		{
			exit_code = print_error_unset(arg[0], arg[i]);
			continue ;
		}
		search_values(arg[i], &name, &value, &mode);
		if (check_name_error(arg[i], &name, &value, &exit_code))
			continue ;
		exec_export(name, value, mode, envp);
	}
	return (exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:23:48 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/02 13:03:58 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	print_export(t_envp *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		else 
			printf("declare -x %s\n", env->name);
		env = env->next;
	}
	return (0);
}

void	search_values(char *arg, char **name, char **value, int *mode)
{
	int	i;

	i = -1;
	*mode = NAME_ONLY;
	while (arg[++i])
	{
		if (arg[i] == '=')
		{
			*mode = CREATE_MODE;
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
/*	if (*mode == CREATE_MODE)
	{
		*name = ft_substr(arg, 0, i);
	   	*value = ft_substr(arg, i + 1, ft_strlen(arg));
	}
	else if (*mode == APPEND_MODE)
	{
		*name = ft_substr(arg, 0, i - 1);
	   	*value = ft_substr(arg, i + 1, ft_strlen(arg));	
	}
	else 
	{
			*name = ft_substr(arg, 0, i);
	//	*value = NULL;
	}*/
}


int	ft_export(t_envp **envp, char **arg)
{
	int	exit_code;
	int	i;
//	int	j;
	char	*name;
	char	*value;
	int		mode;

	name = NULL;
	value = NULL;
	exit_code = 0;
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
	//	exec_export





	/*	if (!ft_strncmp(arg[i], "_", 2))
			continue ;
		j = 0;
		while (arg[i][++j] && arg[i][j] != '=')
			if (arg[i][j] != '_' && !(ft_isalnum(arg[i][j])))
			{
				
				exit_code = print_error_unset(arg[0], arg[i]);

			}
	*/}
		printf("name:%s, value:%s, mode %d\n", name, value, mode);
	return (exit_code);
}

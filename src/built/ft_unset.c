/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:08:47 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/02 12:53:28 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error_unset(char *cmd, char *arg)
{
	ft_putstr_fd(cmd, 2);
	write(2, ": `", 3);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

void	delete_one_node(t_envp **envp)
{
		free((*envp)->name);
		free((*envp)->value);
		free(*envp);
		*envp = NULL;
}

void	delete_first_node(t_envp **envp)
{
	*envp = (*envp)->next;
	(*envp)->prev = NULL;
}

void	delete_env(t_envp **envp, char *arg)
{
	t_envp	*env;

	env = *envp;
	while (env)
	{
		if (!(ft_strncmp(env->name, arg, ft_strlen(arg) + 1)))
		{
			if (!env->prev && !env->next)
				return (delete_one_node(envp));
			else if (!env->prev)
				delete_first_node(envp);	
			else
				env->prev->next = env->next;
			if (env->next && env->prev)
				env->next->prev = env->prev;
			free(env->name);
			free(env->value);
			free(env);
			env = NULL;	
			return ;
		}
		env = env->next;
	}
}

int	ft_unset(t_envp **envp, char **arg)
{
	int		i;
	int		j;
	int		exit_code;

	exit_code = 0;
	i = 0;	
	while (arg[++i])
	{
		if (arg[i][0] != '_' && !(ft_isalpha(arg[i][0])))
			exit_code = print_error_unset(arg[0], arg[i]);
		j = 0; 
		while (arg[i][++j])
			if (arg[i][j] != '_' && !(ft_isalnum(arg[i][j])))
				exit_code = print_error_unset(arg[0], arg[i]);
		delete_env(envp, arg[i]);
	}
	return (exit_code);
}

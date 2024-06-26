/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:10:06 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/31 19:09:06 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_nodes(t_envp *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	env_to_array(char ****env, t_envp *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		(*env)[i] = malloc(sizeof(char *) * 3);
		if (!(*env)[i])
			return (malloc_error());
		(*env)[i][0] = ft_strdup(envp->name);
		if (envp->value)
			(*env)[i][1] = ft_strdup(envp->value);
		else
			(*env)[i][1] = NULL;
		(*env)[i][2] = NULL;
		i ++;
		envp = envp->next;
	}
	(*env)[i] = NULL;
}

void	swap_data(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	sort_env_array(char ****env, int len)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1)
		{
			k = 0;
			while ((*env)[j][0][k] && (*env)[j + 1][0][k] \
									&& (*env)[j][0][k] == (*env)[j + 1][0][k])
				k++;
			if ((*env)[j][0][k] > (*env)[j + 1][0][k])
			{
				swap_data(&(*env)[j][0], &(*env)[j + 1][0]);
				swap_data(&(*env)[j][1], &(*env)[j + 1][1]);
			}
			j++;
		}
		i++;
	}
}

int	print_export(t_envp *envp)
{
	char	***env;
	int		i;
	int		len;

	len = count_nodes(envp);
	env = malloc(sizeof(char *) * (len + 1));
	if (!env)
		return (EXIT_FAILURE);
	env_to_array(&env, envp);
	sort_env_array(&env, len);
	i = 0;
	while (env[i])
	{
		if (env[i][1])
			printf("declare -x %s=\"%s\"\n", env[i][0], env[i][1]);
		else
			printf("declare -x %s\n", env[i][0]);
		i++;
	}
	free_exp_array(env);
	return (EXIT_SUCCESS);
}

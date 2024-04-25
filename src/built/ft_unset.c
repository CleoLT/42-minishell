/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:08:47 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/25 17:38:10 by cle-tron         ###   ########.fr       */
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

void	delete_env(t_envp **env)
{
	
printf("delete %s\n", (*env)->name);

}

void	ft_unset(t_envp **envp, char **arg)
{
	int		i;
	int		j;
	int		exit_code;
	t_envp	*env; 

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
	
		env = *envp;
		while (env)
		{
			if (!(ft_strncmp(env->name, arg[i], ft_strlen(arg[i]) + 1)))
			{
				delete_env(&env);
				break ;
			}
			env = env->next;
		}
	}
	exit(exit_code);
}

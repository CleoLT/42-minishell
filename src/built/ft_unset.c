/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:08:47 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/24 18:44:46 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_envp **env, char **arg)
{
	int	i;
	int	exit_code;

	exit_code = 0;
	i = 1;
	if (!arg[i])
	   return ;	
	while (arg[i])
	{
		if (arg[i][0] != '_' || ft_isalpha(arg[i][0]) != 0)
			printf("error syntax\n");
		
		i++;
	}



	exit(exit_code);
printf("%s\n", (*env)->name);
}

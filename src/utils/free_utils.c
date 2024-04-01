/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:37:01 by irozhkov          #+#    #+#             */
/*   Updated: 2024/04/01 14:59:26 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void static	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

//	if (!cmd->next && cmd)
//	{
//		free(cmd);
//		free_arr(cmd->arg);
//	}
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_arr(tmp->arg);
		free(tmp);
	}
}

int	free_tools(t_tools *tools)
{
	free(tools->str);
//	free_arr(tools->cmd->arg);
	free_cmd(tools->cmd);

	return (1);
}

void	free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

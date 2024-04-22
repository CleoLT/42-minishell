/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:37:01 by irozhkov          #+#    #+#             */
/*   Updated: 2024/04/22 12:30:54 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void static free_token(t_token **lexer_list)
{
	t_token *tmp;

	if (!*lexer_list)
		return ;
	while (*lexer_list)
	{
		tmp = (*lexer_list)->next;
		if ((*lexer_list)->str)
			free((*lexer_list)->str);
		free(*lexer_list);
		*lexer_list = tmp;
	}
	*lexer_list = NULL;
}

void static free_envp(t_envp **envp_list)
{
	t_envp *tmp;

	if (!*envp_list)
		return ;
	while (*envp_list)
	{
		tmp = (*envp_list)->next;
		if ((*envp_list)->name)
			free((*envp_list)->name);
		if ((*envp_list)->value)
			free((*envp_list)->value);
		free(*envp_list);
		*envp_list = tmp;
	}
	*envp_list = NULL;
}
/*
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
}*/

int	free_tools(t_tools *tools)
{
	free(tools->str);
//	free_arr(tools->cmd->arg);
//	free_cmd(tools->cmd);
	free_token(&tools->lexer_list);
	free_envp(&tools->envp_list);
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

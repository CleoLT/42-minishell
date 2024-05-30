/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:37:01 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/30 16:44:15 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void static	free_token(t_token **lexer_list)
{
	t_token	*tmp;

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

void	free_envp(t_envp **envp_list)
{
	t_envp	*tmp;

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

void static	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp->arg);
		free_array_pt(tmp->infile);
		free_array_pt(tmp->outfile);
		free(tmp);
	}
}

int	free_tools_loop(t_tools *tools, char *line)
{
	delete_env(&tools->envp_list, "_");
	free(line);
	free(tools->str);
	free_token(&tools->lexer_list);
	free_cmd(tools->cmd);
	free_arr(tools->path);
	return (1);
}

void	free_tools(t_tools *tools)
{
	free_arr(tools->envp);
	free_envp(&tools->envp_list);
	free_arr(tools->path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:37:01 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/16 18:44:20 by cle-tron         ###   ########.fr       */
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

void free_envp(t_envp **envp_list)
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
	
void static	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_arr(tmp->arg);
	//	free_array_pt(tmp->infile);
	//	free_array_pt(tmp->outfile);
	
		if (tmp->infile)
		{
			i = 0;
			while(tmp->infile[i])
			{
				if (tmp->infile[i][1])
					free(tmp->infile[i][0]); //chapuza para liberar en caso de heredoc
				free(tmp->infile[i++]);
			}
			free(tmp->infile);
		}
		if (tmp->outfile)
		{
			i = 0;
			while(tmp->outfile[i])
				free(tmp->outfile[i++]);
			free(tmp->outfile);
		}


		free(tmp);
	}
}

int	free_tools_loop(t_tools *tools, char *line)
{
	delete_env(&tools->envp_list, "_");
	free(line);
	free(tools->str);
	free_cmd(tools->cmd);
	free_token(&tools->lexer_list);
//	free_envp(&tools->envp_list);
	free_arr(tools->path);
	return (1);
}

void	free_arr(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_array_pt(char ***array)
{
	int i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
	
		free_arr(array[i++]);
	}
	free(array);
}

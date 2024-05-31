/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:54:43 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/31 14:44:19 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_addback(t_cmd *node, t_cmd **cmd_list)
{
	t_cmd	*tmp;

	tmp = *cmd_list;
	if (*cmd_list == NULL)
	{
		*cmd_list = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
}

void	create_node_cmd(t_cmd **cmd_list, int indx)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		ft_error("malloc function", errno);
	node->arg = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->lexer_indx = indx;
	node->ar = 0;
	node->in = 0;
	node->out = 0;
	cmd_addback(node, cmd_list);
}

int	size_list(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	create_cmd_list(t_tools *tools, int *error)
{
	t_token	*lexer_tmp;
	int		i;

	lexer_tmp = tools->lexer_list;
	if (lexer_tmp && lexer_tmp->type == PIPE)
	{
		*error = err_syntax(PIPE);
		return ;
	}
	while (lexer_tmp)
	{
		if (lexer_tmp->next)
		{
			if (lexer_tmp->type == PIPE && lexer_tmp->next->type != PIPE)
			{
				if (lexer_tmp->next->next->type != PIPE)
					create_node_cmd(&tools->cmd, lexer_tmp->indx);
			}
		}
		i = lexer_tmp->indx;
		lexer_tmp = lexer_tmp->next;
	}
	create_node_cmd(&tools->cmd, i + 1);
	tools->t_cmd_size = size_list(tools->cmd);
}

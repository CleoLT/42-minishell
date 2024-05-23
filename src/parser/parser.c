/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:50:15 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/23 13:24:01 by cle-tron         ###   ########.fr       */
/* ************************************************************************** */

#include "minishell.h"

void	print_cdm_list(t_cmd *cmd)
{
	
	int i;
	while (cmd)
	{
		printf("node: ");
		if (cmd->infile)
		{
			i = 0;
			while (cmd->infile[i])
			{
				if (cmd->infile[i][1])
					printf("<<%s ", cmd->infile[i][0]);
				else
					printf("<%s ", cmd->infile[i][0]);
				i++;
			}
		}
		if (cmd->outfile)
		{
			i = 0;
			while (cmd->outfile[i])
			{
				if (cmd->outfile[i][1])
					printf(">>%s ", cmd->outfile[i][0]);
				else
					printf(">%s ", cmd->outfile[i][0]);
				i++;
			}
		}
		i = 0;
		if (cmd->arg)
		{
		while (cmd->arg[i])
			printf("-%s- ", cmd->arg[i++]);
		}
		if (cmd->next)
			printf("| ");
		else
			printf("\n");
		cmd = cmd->next;
	}
}
void	fill_files(int *i, char **files, t_token **lex, int *count)
{
	t_token *file;

	file = NULL;
	if (!(*lex)->next)
		return ;
	else if ((*lex)->next->type >= STRING)
		file = (*lex)->next;
	else if ((*lex)->next->type == SPACE2 && (*lex)->next->next->type >= STRING)
	{
		file = (*lex)->next->next;
		*i += 1;
	}
	else if (file == NULL)
		return ;
	files[0] = file->str;
	if ((*lex)->type == INPUT || (*lex)->type == OUTPUT)
		files[1] = NULL;
	else
		files[1] = "hd";
	files[2] = NULL;
	*i += 1;
	*lex = file;
	*count += 1;
	
	/*	if ((*lex)->next && (*lex)->next->type >= STRING)
	{
			
		files[0] = (*lex)->next->str;
		if ((*lex)->type == INPUT || (*lex)->type == OUTPUT)
			files[1] = NULL;
		else
			files[1] = "hd";
		files[2] = NULL;
		*i += 1;
		*lex = (*lex)->next;
		*count += 1;
	}*/
}

void	fill_cmd(t_tools *tools)
{
	t_cmd	*cmd;
	t_token	*lex;
	int		i;

	cmd = tools->cmd;
	lex = tools->lexer_list;
	i = 0;
	while (cmd)
	{
		cmd->ar = 0;
		cmd->in = 0;
		cmd->out = 0;
		while (i < cmd->lexer_indx && lex)
		{
			if (lex->type >= STRING && cmd->arg)
				cmd->arg[cmd->ar++] = lex->str;
			else if (lex->type == INPUT || lex->type == HEREDOC)
				fill_files(&i, cmd->infile[cmd->in], &lex, &cmd->in);
			else if (lex->type == OUTPUT || lex->type == APPEND)
				fill_files(&i, cmd->outfile[cmd->out], &lex, &cmd->out);
			i++;
			lex = lex->next;
		}
		cmd = cmd->next;
	}
}

int	ft_parser(t_tools *tools)
{
	int	error;
	
	error = 0;
	create_cmd_list(tools, &error);
	if (!tools->lexer_list)
		return (1);
	malloc_and_errors_cmd(tools, &error);
	if (error)
	{
		tools->exit_code = 258;
		return (error);
	}
	fill_cmd(tools);
//	print_cdm_list(tools->cmd); //BORRAR FUNCTION
	if (error)
		tools->exit_code = 258;
	if (tools->cmd->arg == NULL)
		tools->cmd->arg = ft_split("  ", ' ');
	return (error);
}

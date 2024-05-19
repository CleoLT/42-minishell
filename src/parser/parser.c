/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:50:15 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/19 14:41:05 by cle-tron         ###   ########.fr       */
/* ************************************************************************** */

#include "minishell.h"
/*
void	print_cdm_list(t_cmd *cmd)
{
	int i;
	while (cmd)
	{
		printf("node %d\n", cmd->lexer_indx);
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
			printf("%s ", cmd->arg[i++]);
		if (cmd->next)
			printf("| ");
		else
			printf("\n");
		}
		cmd = cmd->next;
	}
}*/



void	fill_cmd(t_tools *tools)
{
	t_cmd	*cmd;
	t_token	*lex;
	int		i;
	int		arg;
	int		infile;
	int		outfile;

	cmd = tools->cmd;
	lex = tools->lexer_list;
	i = 0;
	while (cmd)
	{
		arg = 0;
		infile = 0;
		outfile = 0;
		while (i < cmd->lexer_indx && lex)
		{
			if (lex->type >= STRING)
				cmd->arg[arg++] = lex->str;
			else if (lex->type == INPUT || lex->type == HEREDOC)
			{
				if (lex->next && lex->next->type >= STRING)
				{
					cmd->infile[infile][0] = lex->next->str;
					if (lex->type == INPUT)
						cmd->infile[infile][1] = NULL;
					else
						cmd->infile[infile][1] = "hd";
					cmd->infile[infile++][2] = NULL;
					i++;
					lex = lex->next;
				}
			}
			else if (lex->type == OUTPUT || lex->type == APPEND)
			{
				if (lex->next && lex->next->type >= STRING)
				{
					outfile++;
					i++;
					lex = lex->next;
				}
			}

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
	
//	print_cdm_list(tools->cmd);

	if (error)
		tools->exit_code = 258;
	return (error);
}

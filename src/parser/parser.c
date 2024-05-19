/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:19:46 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/18 17:44:31 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	/*	if (cmd->outfile)
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
		}*/
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
}

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
	cmd_addback(node, cmd_list);
}

int	size_list(t_cmd *cmd)
{
	int count;

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
			if (lexer_tmp->type == PIPE && lexer_tmp->next->type != PIPE  )
			create_node_cmd(&tools->cmd, lexer_tmp->indx);
		}
		i = lexer_tmp->indx;
		lexer_tmp = lexer_tmp->next;
	}
	create_node_cmd(&tools->cmd, i + 1);
	tools->t_cmd_size = size_list(tools->cmd);
}


/*
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
		while (i < cmd->lexer_indx)
		{
			if (lex->type >= STRING)		
			i++;
			lex = lex->next;
		}
		cmd = cmd->next;
	}

}*/
void	create_cmd_malloc(t_cmd **cmd, int arg, int in, int out)
{
	int	i;
	int	j;

	i = 0;
	(*cmd)->arg = malloc(sizeof(char *) * (arg + 1));
	while (i <= arg)
	{
		printf("%i\n", i);
		(*cmd)->arg[i] = NULL;
		i++;
	}
	i = 0;
	(*cmd)->infile = malloc(sizeof(char *) * (in + 1));
	while (i <= in)
	{
		(*cmd)->infile[i] = malloc(sizeof(char *) * 3);
		j = 0;
		while (j <= 3)	
			(*cmd)->infile[i][j++] = NULL;
		i++;
	}
	i = 0;
	(*cmd)->outfile = malloc(sizeof(char *) * (out + 1));
	while (i <= out)
		(*cmd)->outfile[i++] = malloc(sizeof(char *) * 3);
}

void	malloc_and_errors_cmd(t_tools *tools, int *err)
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
				arg++;
			else if (lex->type == INPUT || lex->type == HEREDOC)
			{
				if (lex->next && lex->next->type >= STRING)
				{
					infile++;
					i++;
					lex = lex->next;
				}
				else
				{	
					if (!lex->next)
						*err = err_syntax(-1);
					else
						*err = err_syntax(lex->next->type);
					return ;
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
				else 
				{	
					if (!lex->next)
						*err = err_syntax(-1);
					else
						*err = err_syntax(lex->next->type);
					return ;
				}
			}
			else if ((lex->type == PIPE && lex->prev->type == PIPE) || \
											(lex->type == PIPE && !lex->next))
			{
		
				*err = err_syntax(PIPE);
				return ;
			}	
			i++;
			lex = lex->next;
		}
		printf("i: %d, arg: %d, infile: %d, outfile: %d\n", i, arg, infile, outfile);
		//make function to reserve malloc for arg, infile, outfile
		create_cmd_malloc(&cmd, arg, infile, outfile);
		cmd = cmd->next;
	}
}

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
					cmd->infile[infile++][0] = lex->next->str;
					cmd->infile[infile++][1] = NULL;
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
		return (0);
	malloc_and_errors_cmd(tools, &error);
	if (error)
	{
		tools->exit_code = 258;
		return (error);
	}
	fill_cmd(tools);
	
	print_cdm_list(tools->cmd);

	if (error)
		tools->exit_code = 258;
	return (error);
}

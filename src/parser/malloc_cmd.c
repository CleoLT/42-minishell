/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:59:31 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/31 14:47:58 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_files(char ****files, int count)
{
	int	i;
	int	j;

	i = 0;
	*files = malloc(sizeof(char *) * (count + 1));
	while (i < count)
	{
		(*files)[i] = malloc(sizeof(char *) * 3);
		j = 0;
		while (j < 3)
			(*files)[i][j++] = NULL;
		i++;
	}
	(*files)[count] = NULL;
}

void	create_cmd_malloc(t_cmd **cmd)
{
	int	i;

	i = 0;
	if ((*cmd)->ar)
	{
		(*cmd)->arg = malloc(sizeof(char *) * ((*cmd)->ar + 1));
		while (i <= (*cmd)->ar)
			(*cmd)->arg[i++] = NULL;
	}
	if ((*cmd)->in)
		malloc_files(&(*cmd)->infile, (*cmd)->in);
	if ((*cmd)->out)
		malloc_files(&(*cmd)->outfile, (*cmd)->out);
}

void	calculate_files(int *i, t_cmd *cmd, int *err, t_token **lex)
{
	if ((*lex)->type == INPUT || (*lex)->type == HEREDOC)
		cmd->in++;
	else if ((*lex)->type == OUTPUT || (*lex)->type == APPEND)
		cmd->out++;
	if ((*lex)->next && (*lex)->next->type >= STRING)
	{
		*i += 1;
		*lex = (*lex)->next;
	}
	else if ((*lex)->next && (*lex)->next->next && \
			(*lex)->next->type == SPACE2 && (*lex)->next->next->type >= STRING)
	{
		*i += 2;
		*lex = (*lex)->next->next;
	}
	else
	{
		if (!(*lex)->next)
			*err = err_syntax(-1);
		else
			*err = err_syntax((*lex)->next->type);
		return ;
	}
}

int	error_pipe(t_token *lex)
{
	if (lex->type == PIPE && lex->prev->type == PIPE)
		return (1);
	else if (lex->type == PIPE && !lex->next)
		return (1);
	else if (lex->type == PIPE && lex->prev->type == SPACE2 && \
									lex->prev->prev->type == PIPE)
		return (1);
	return (0);
}

void	malloc_and_errors_cmd(t_tools *tools, int *err)
{
	t_cmd	*cmd;
	t_token	*lex;
	int		i;

	cmd = tools->cmd;
	lex = tools->lexer_list;
	i = 0;
	while (cmd)
	{
		while (i < cmd->lexer_indx && lex)
		{
			if (check_string(lex))
				cmd->ar++;
			else if (lex->type >= INPUT && lex->type <= APPEND)
				calculate_files(&i, cmd, err, &lex);
			else if (error_pipe(lex))
				*err = err_syntax(PIPE);
			if (*err)
				return ;
			lex = lex->next;
			i++;
		}
		create_cmd_malloc(&cmd);
		cmd = cmd->next;
	}
}
//	printf("i: %d, arg: %d, infile: %d, outfile: %d\n", i, \
//	cmd->ar, cmd->in,cmd->out);

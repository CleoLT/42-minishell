/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:04:09 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/30 16:18:36 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lexer_list(t_token *lexer_list)
{
	while (lexer_list)
	{
		printf("type: %d\n str: %s\n indx: %d\n ----\n", lexer_list->type, \
										lexer_list->str, lexer_list->indx);
		printf("\npointer: %p\n", lexer_list);
		lexer_list = lexer_list->next;
	}
}

void	print_infiles(char ***file)
{
	int	i;

	i = 0;
	if (file)
	{
		while (file[i])
		{
			if (file[i][1])
				printf("<<%s ", file[i][0]);
			else
				printf("<%s ", file[i][0]);
			i++;
		}
	}
}

void	print_outfiles(char ***file)
{
	int	i;

	i = 0;
	if (file)
	{
		while (file[i])
		{
			if (file[i][1])
				printf(">>%s ", file[i][0]);
			else
				printf(">%s ", file[i][0]);
			i++;
		}
	}
}

void	print_cdm_list(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		printf("node: ");
		print_infiles(cmd->infile);
		print_outfiles(cmd->outfile);
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

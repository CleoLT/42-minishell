/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:53:04 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/22 17:50:19 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
/*
void	init_index(t_token *lex)
{
	int i;

	i = 0;
	while (lex)
	{
		lex->indx = i++;
		lex = lex->next;
	}
}
*/
void	ft_lexerdeltype(t_tools *tools, int del)
{
	t_token	*current;
	t_token	*temp;

	current = tools->lexer_list;
	while (current != NULL)
	{
		if (current->type == del)
		{
			temp = current->next;
			if (current->prev != NULL)
				current->prev->next = current->next;
			else
				tools->lexer_list = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			free(current->str);
			free(current);
			current = temp;
		}
		else
			current = current->next;
	}
//	init_index(tools->lexer_list);
}

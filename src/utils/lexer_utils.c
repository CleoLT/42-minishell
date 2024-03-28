/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:30:31 by irozhkov          #+#    #+#             */
/*   Updated: 2024/03/26 19:48:47 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	token_addback(t_token **lexer_list, t_token *node)
{
	t_token	*tmp;

	tmp = *lexer_list;
	if (*lexer_list == NULL)
	{
		*lexer_list = node;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
}

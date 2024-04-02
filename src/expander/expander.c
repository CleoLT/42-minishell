/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:50:26 by irozhkov          #+#    #+#             */
/*   Updated: 2024/04/02 16:49:50 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	expander_reader(t_tools *tools)
{
	while (tools->lexer_list != NULL)
	{
		if ((tools->lexer_list->type == STRING)
			|| (tools->lexer_list->type == STRINGD))
		{
			if (ft_strchr(tools->lexer_list->str, '$') != NULL)
				printf("-44-->%s\n", ft_strchr(tools->lexer_list->str, '$'));
			else
				printf("-%s-->\n", ft_strchr(tools->lexer_list->str, '$'));
		}
		else if (tools->lexer_list->type == STRINGS)
			printf("-(null_opt)-->\n");
		tools->lexer_list = tools->lexer_list->next;
	}
	return (1);
}

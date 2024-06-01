/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:42:07 by irozhkov          #+#    #+#             */
/*   Updated: 2024/06/01 11:43:04 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	change_tilde_value(t_tools *tools)
{
	t_token	*lex;
	char	*tmp;
	char	*home;

	lex = tools->lexer_list;
	while (lex)
	{
		if (lex->type == STRING && lex->str[0] == '~')
		{
			home = getenv("HOME");
			if (!home)
				return ;
			if (lex->str[1] == '\0' || lex->str[1] == '/')
			{
				tmp = ft_strjoin(home, lex->str + 1);
				free(lex->str);
				lex->str = tmp;
			}
		}
		lex = lex->next;
	}
}

void	lexer_token(t_tools *tools, char *line)
{
	tools->str = ft_strtrim(line, " ");
	if (!tools->str)
		ft_error("exit", errno);
	if (!token_reader(tools))
		ft_error("bad lexer", errno);
	if (!expander_reader(tools))
		ft_error("bad expander", errno);
	change_tilde_value(tools);
}

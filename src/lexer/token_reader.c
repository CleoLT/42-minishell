/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:32:50 by irozhkov          #+#    #+#             */
/*   Updated: 2024/03/30 15:44:18 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int check_token(int c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (INPUT);
	else if (c == '>')
		return (OUTPUT);
	return (0);
}

int	token_handler(char *s, int i, t_token **lexer_list)
{
	int	token;

	token = check_token(s[i]);
	if ((token == INPUT) && (check_token(s[i + 1]) == INPUT))
	{
		if (!token_addnode(NULL, HEREDOC, lexer_list))
			return (-1);
		return (2);
	}
	else if ((token == OUTPUT) && (check_token(s[i + 1]) == OUTPUT))
	{
		if (!token_addnode(NULL, APPEND, lexer_list))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (!token_addnode(NULL, token, lexer_list))
			return (-1);
		return (1);
	}
	return (0);
}

int	token_addnode (char *s, int token, t_token **lexer_list)
{
	t_token *node;
	static int	indx;

	indx = 0;
	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (0);
	node->type = token;
	node->str = s;
	node->indx = indx++;
	node->next = NULL;
	node->prev = NULL;
	token_addback(lexer_list, node);
	return (1);
}

int	get_str(char *s, int i, t_token **lexer_list)
{
	int	len;

	len = 0;
	while (s[i + len] && !(check_token(s[i + len]))
		&& s[i + len] != 34 && s[i + len] != 39 && ft_isspace(s[i + len]) != 1)
		len++;
	if (!token_addnode(ft_substr(s, i, len), 6, lexer_list))
		return (-1);
	return (len);
}

int	token_reader(t_tools *tools)
{
	int	i;
	int j;

	i = 0;
	while (tools->str[i])
	{
		j = 0;
		if (ft_isspace(tools->str[i]) == 1)
			j = spaces_handler(tools->str, i, &tools->lexer_list);
		else if (check_token(tools->str[i]))
			j = token_handler(tools->str, i, &tools->lexer_list);
		else if ((tools->str[i] == 34) || (tools->str[i] == 39))
			j = quotes_handler(tools->str, i, tools->str[i], &tools->lexer_list); 
		else
			j = get_str(tools->str, i, &tools->lexer_list);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}

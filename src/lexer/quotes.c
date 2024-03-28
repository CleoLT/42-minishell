/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:55:27 by irozhkov          #+#    #+#             */
/*   Updated: 2024/03/28 20:07:20 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	quotes_handler(char *s, int i, char quote, t_token **lexer_list)
{
	int j;

	j = 0;
	if (s[i + j] == quote)
	{
		j++;
		while (s[i + j] && (s[i + j] != quote))
			j++;
		j++;
	}
	if (quote == 34)
	{
		if (!token_addnode(ft_substr(s, i, j), 7, lexer_list))
			return (-1);
	}
	else if (quote == 39)
	{
		if (!token_addnode(ft_substr(s, i, j), 8, lexer_list))
			return (-1);
	}
	return (j);
}

int	closed_quotes(char *s, int i, int *counter, int quote)
{
	int	j;

	j = i + 1;
	*counter += 1;
	while (s[j] && (s[j] != quote))
		j++;
	if (s[j] == quote)
		*counter += 1;
	return (j - i);
}	


int	count_quotes(char *str)
{
	int	i;
	int	s;
	int	d;

	i = -1;
	s = 0;
	d = 0;
	while (str[++i])
	{
		if (str[i] == 34)
			i += closed_quotes(str, i, &d, 34);
		if (str[i] == 39)
			i += closed_quotes(str, i, &s, 39);
	}
	if (((d > 0) && (d % 2 != 0)) || ((s > 0) && (s % 2 != 0)))
		return (0);
	return (1);
}

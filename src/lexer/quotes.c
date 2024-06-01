/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:55:27 by irozhkov          #+#    #+#             */
/*   Updated: 2024/06/01 11:56:35 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	quote_addnode(char *sub_str, char quote, t_token **lexer_list, int c)
{
	if (quote == 34)
	{
		if (!token_addnode(sub_str, 7, lexer_list, c))
			return (-1);
	}
	else if (quote == 39)
	{
		if (!token_addnode(sub_str, 8, lexer_list, c))
			return (-1);
	}
	return (1);
}

void	quotes_str(const char *s, char *sub_str, int i)
{
	int		k;
	char	quote;

	quote = s[i];
	k = 0;
	i += 1;
	while (s[i] && (s[i] != quote))
	{
		sub_str[k] = s[i];
		k++;
		i++;
	}
	sub_str[k] = '\0';
}

int	quotes_handler(const char *s, int i, t_token **lexer_list, int c)
{
	int		j;
	char	*sub_str;
	char	quote;

	j = 0;
	quote = s[i];
	sub_str = (char *)malloc(sizeof(char) * (ft_strlen(s) - 1));
	if (!sub_str)
		return (-1);
	if (quote == 34 || quote == 39)
	{
		quotes_str(s, sub_str, i);
		quotes_handler_extra(sub_str, quote, lexer_list, c);
	}
	if (s[i + j] == quote)
	{
		while (s[i + (++j)] && (s[i + j] != quote))
			continue ;
		j++;
	}
	return (j);
}

int	closed_quotes(const char *s, int i, int *counter, int quote)
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

int	count_quotes(const char *str)
{
	int	i;
	int	s;
	int	d;

	i = -1;
	s = 0;
	d = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == 34)
			i += closed_quotes(str, i, &d, 34);
		if (str[i] == 39)
			i += closed_quotes(str, i, &s, 39);
		if (str[i] == '\0')
			break ;
	}
	if (((d > 0) && (d % 2 != 0)) || ((s > 0) && (s % 2 != 0)))
		return (0);
	return (1);
}

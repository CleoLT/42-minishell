/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:50:26 by irozhkov          #+#    #+#             */
/*   Updated: 2024/04/22 12:39:19 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
/*
char	*expand_str(t_tools *tools, char *s, int indx[][2], int c)
{
	char	*tmp;
	char	*word;
	int		i;
	int		j;
	int		k;
	int		w;

//	printf("---> expand_str s original: %s\n", s);
	tmp = malloc(sizeof(char) * (newstr_len(tools, s, indx, c) + 1));
//	printf("---> expand_str s malloc original: %s\n", s);
	if (!tmp)
		return (NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		j = 0;
		while (j < c)
		{
			while (s[i] != '$' && s[i])
			{
				tmp[k] = s[i];
				i++;
				k++;
			}
			if (s[i] == '$')
			{
				w = 0;
				word = (char *)malloc(sizeof(char) * len_expander(tools, s, indx[j][0], indx[j][1])); //HERE IS THE LEAK !!!!!!!!!!!!!!!!!
				if (!word)
					return (NULL);
//				word = expand_word(tools, s, indx[j][0], indx[j][1] - indx[j][0]);
				expand_word(tools, s, &indx[j], word);
//				printf("---> expand_str word pointer: %p\n", word);
//				printf("---> here word: %s\n", word);
				if (ft_strlen(word) != 0)
				{
					while (word[w])
					{
						tmp[k] = word[w];
						k++;
						w++;
					}
					free(word);
				}
				else
					free(word);
			}
			i += (indx[j][1] - indx[j][0]);
			j++;
		}
	}
	tmp[k] = '\0';
	return (tmp);
}

char	*expand_indx(t_tools *tools, char *s, int c, t_indx *dollar_indx)
{
	int		dollar_indx[c][2];
	int		i;
	int		j;

	printf("---> expand_indx c = %d\n", c);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			dollar_indx[j][0] = i;
			while (s[i] && ft_isspace(s[i]) != 1)
				i++;
			dollar_indx[j][1] = i;
			j++;
		}
		i++;
	}
	j = 0;
	while (dollar_indx[j][i] != -1)
	{
		printf("---> expand_indx i = %d, j = %d\n", dollar_indx[j][0], dollar_indx[j][1]);
		j++;
	}
//	if (c != 0)
//		return (expand_str(tools, s, dollar_indx, c));
	return (s);
}

int	expander_reader(t_tools *tools)
{
	int		counter;
	char	*tmp;
	t_token *original_lex;
	t_indx	*dollar_indx;

	counter = 0;
	original_lex = tools->lexer_list;
	while (tools->lexer_list != NULL)
	{
		if ((tools->lexer_list->type == STRING)
			|| (tools->lexer_list->type == STRINGD))
			if (is_dollar(tools->lexer_list->str) >= 0)
			{
//				printf("--expander_reader--> pointer: %p\n", tools->lexer_list->str);
				counter = count_dollar(tools->lexer_list->str);
				printf("---> before: %s\n", tools->lexer_list->str);
				if (counter > 0)
				{
					tmp = expand_indx(tools, tools->lexer_list->str, counter, dollar_indx);
//					free(tools->lexer_list->str);
//					tools->lexer_list->str = tmp;
					free(tmp);
				}
				printf("---> after: %s\n", tools->lexer_list->str);
			}
//		printf("--->pointer exp: %p\n", tools->lexer_list->str);
		tools->lexer_list = tools->lexer_list->next;
	}
	tools->lexer_list = original_lex;
	return (1);
}*/

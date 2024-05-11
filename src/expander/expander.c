/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:50:26 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/11 16:41:23 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void static	ft_chartochar(char *temp, char *temp_word, int *i)
{
	int	k;

	k = 0;
	while (temp_word[k])
	{
		temp[(*i)] = temp_word[k];
		(*i)++;
		k++;
	}
}

void static	expand_str(t_tools *tools, char *temp, const char *s)
{
	char	*temp_word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[j] != '\0')
	{
		while (s[j] != '$')
		{
			temp[i] = s[j];
			i++;
			j++;
		}
		temp_word = expand_indx(tools, (char *)s, j);
		if (temp_word != NULL)
			ft_chartochar(temp, temp_word, &i);
		j = dollar_len(s, j);
		free (temp_word);
	}
	temp[i] = '\0';
}

int	expander_newlen(t_tools *tools, const char *s)
{
	int			start_index;
	int			end_index;
	int			len;
	const char	*dollar_pos;
	const char	*e_pos;

	start_index = -1;
	end_index = -1;
	len = ft_strlen(s);
	dollar_pos = s;
	while (*dollar_pos != '\0')
	{
		if (*dollar_pos == '$')
		{
			start_index = (int)(dollar_pos - s);
			e_pos = dollar_pos + 1;
			while ((ft_isspace(*e_pos) != 1) && *e_pos != '\0' && *e_pos != '$')
				e_pos++;
			end_index = (int)(e_pos - s);
			len -= (end_index - start_index);
			len += expander_value_len(tools, s, start_index, end_index);
		}
		dollar_pos++;
	}
	return (len);
}

int	expander_reader(t_tools *tools)
{
	char		*temp;
	t_token		*original_lex;

	original_lex = tools->lexer_list;
	while (tools->lexer_list != NULL)
	{
		if (((tools->lexer_list->type == STRING)
			|| (tools->lexer_list->type == STRINGD))
			&& (count_dollar(tools->lexer_list->str) > 0))
		{
			temp = (char *)malloc(sizeof(char) * (expander_newlen(tools,
							tools->lexer_list->str) + 1));
			if (!temp)
				return (0);
			expand_str(tools, temp, tools->lexer_list->str);
			free(tools->lexer_list->str);
			tools->lexer_list->str = temp;
		}
		tools->lexer_list = tools->lexer_list->next;
	}
	tools->lexer_list = original_lex;
	return (1);
}

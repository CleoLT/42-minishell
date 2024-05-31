/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:58:47 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/31 21:39:17 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	special_len(t_tools *tools, char c)
{
	if (c == '?')
		return (expander_question_len(tools));
	else if (c == '\0')
		return (2);
	else if ((c >= '0') && (c <= '9'))
		return (0);
	else
		return (2);
	return (0);
}

int	newline_len(const char *word)
{
	const char	*temp;
	int			i;
	int			len;

	temp = word;
	i = 0;
	len = 0;
	while (temp[i])
	{
		if (!(temp[i] == '\\' && (temp[i + 1] == 'n' || temp[i + 1] == 't'
					|| temp[i + 1] == 'r')))
		{
			len++;
			i++;
		}
		else
		{
			len++;
			i += 2;
		}
	}
	return (len);
}

void static	expand_newlinesym(char *temp, char c, int *i, int *j)
{
	if (c == 'n')
		temp[(*j)] = 10;
	else if (c == 't')
		temp[(*j)] = 9;
	else if (c == 'r')
		temp[(*j)] = 13;
	(*i) += 2;
	(*j)++;
}

char	*expand_newline(char *word)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = (char *)malloc(sizeof(char) * (newline_len(word) + 1));
	if (!temp)
		return (NULL);
	while (word[i])
	{
		if (!(word[i] == '\\' && (word[i + 1] == 'n' || word[i + 1] == 't'
					|| word[i + 1] == 'r')))
		{
			temp[j] = word[i];
			i++;
			j++;
		}
		else
			expand_newlinesym(&temp[j], word[i + 1], &i, &j);
	}
	temp[j] = '\0';
	free(word);
	return (temp);
}

char	*expand_special_other(char c, int *indx)
{
	char	*temp;

	if (c == '\0')
	{
		temp = malloc(2 * sizeof(char));
		if (!temp)
			return (NULL);
		ft_strcpy(temp, "$");
		(*indx) += 1;
	}
	else
	{
		temp = malloc(3 * sizeof(char));
		if (!temp)
			return (NULL);
		temp[0] = '$';
		temp[1] = c;
		temp[2] = '\0';
		(*indx) += 2;
	}
	return (temp);
}

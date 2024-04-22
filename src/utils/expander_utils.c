/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:05:29 by irozhkov          #+#    #+#             */
/*   Updated: 2024/04/22 12:40:08 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
/*
void expand_word(t_tools *tools, char *s, int indx[][2], char *word)
{
	t_envp	*original_envp_list;
	char	*word_den;
	int		w;
	int		flag;

	original_envp_list = tools->envp_list;
	w = 0;
	word_den = (char *)malloc(sizeof(char) * (indx[0][1] - indx[0][0]));
	if (!word_den)
		return ;
	ft_strlcpy(word_den, &s[indx[0][0] + 1], (indx[0][1] - indx[0][0]));
	flag = 0;
	while (tools->envp_list != NULL)
	{
		if (ft_strncmp(word_den, tools->envp_list->name, ft_strlen(tools->envp_list->name)) == 0)
		{
			free(word_den);
			flag = 1;
			break ;
		}
		tools->envp_list = tools->envp_list->next;
	}
	if (flag == 1)
		ft_strlcpy(word, tools->envp_list->value, ft_strlen(tools->envp_list->value) + 1);
	else
	{
		word = "";
		free(word_den);
	}
	tools->envp_list = original_envp_list;
}

int	len_expander(t_tools *tools, char *s, int i, int j)
{
	int		len;
	int		w;
	t_envp	*original_envp_list;
	char	*word;

	original_envp_list = tools->envp_list;
	len = 0;
	w = 0;
	word = (char *)malloc(sizeof(char) * (j - i));
	if (!word)
		return (-1);
	ft_strlcpy(word, &s[i + 1], (j - i)); 
//	printf("---> len_expander WORD: %s\n", word);
	while (tools->envp_list != NULL)
	{
//		printf("---> len_expander NAME: %s\n", tools->envp_list->name);
		if (ft_strncmp(word, tools->envp_list->name, ft_strlen(tools->envp_list->name)) == 0)
			len = ft_strlen(tools->envp_list->value);
		tools->envp_list = tools->envp_list->next;
	}
	tools->envp_list = original_envp_list;
	printf("---> len_expander word pointer: %p\n", word);
	free(word);
	return (len);
}

int newstr_len(t_tools *tools, char *s, int indx[][2], int c)
{
	int		i;
	int 	len[1][3];
	int 	len_total;

	i = 0;
	len_total = 0;
	len[0][0] = 0;
	len[0][1] = 0;
	len[0][2] = 0;
	len[0][0] = ft_strlen(s);
	while (i < c)
	{
//		printf("--->newstr_len CONTROL S: %s\n", s);
		len[0][1] += (indx[i][1] - indx[i][0]);
		len[0][2] += len_expander(tools, s, indx[i][0], indx[i][1]);
		i++;
	}
	printf("--> len[0] = %d, len[1] = %d, len[2] = %d\n", len[0][0], len[0][1], len[0][2]);
	len_total = len[0][0] - len[0][1] + len[0][2];
	return (len_total);
}

int	count_dollar(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s == '$')
			i++;
		s++;
	}
	return (i);
}

int	is_dollar(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}*/

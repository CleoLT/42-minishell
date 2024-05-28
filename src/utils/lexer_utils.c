/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:30:31 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/27 14:46:44 by irozhkov         ###   ########.fr       */
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

char	*ft_strcat(char *dest, const char *src)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int	 ft_doglue(t_token *current)
{
	t_token	*next_node;
	char	*new_str;

	next_node = current->next;
	if ((current->type == 6 || current->type == 7 || current->type == 8)
		&& (next_node->type == 6 || next_node->type == 7 || next_node->type == 8))
	{
		new_str = (char *)malloc(ft_strlen(current->str)
			+ strlen(next_node->str) + 1);
		if (!new_str)
		   return (1);	
		ft_strcpy(new_str, current->str);
		ft_strcat(new_str, next_node->str);
		free(current->str);
		current->str = new_str;
		current->next = next_node->next;
		if (next_node->next)
			next_node->next->prev = current;
		free(next_node->str);
		free(next_node);
		return (1);
	}
	return (0);
}

void	ft_gluenodes(t_tools *tools)
{
	t_token *current;
	int		glued;

	if (!tools || !tools->lexer_list)
		return;
	glued = 1;
	while (glued)
	{
		glued = 0;
		current = tools->lexer_list;
		while (current && current->next)
		{
			if (ft_doglue(current))
			{
				glued = 1;
				break;
			}
			current = current->next;
		}
	}
}

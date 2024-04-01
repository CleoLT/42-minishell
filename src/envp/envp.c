/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:01:46 by irozhkov          #+#    #+#             */
/*   Updated: 2024/04/01 21:55:14 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	envp_addback(t_envp **envp_list, t_envp *node)
{
	t_envp	*tmp;
	
	tmp = *envp_list;
	if (*envp_list == NULL)
	{
		*envp_list = node;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
}

int	envp_addnode(char *n, char *v, t_envp **envp_list)
{
	t_envp	*node;

	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node)
		return (0);
	node->name = n;
	node->value = v;
	node->next = NULL;
	node->prev = NULL;
	envp_addback(envp_list, node);
	return (1);
}

int	envp_reader(t_tools *tools)
{
	int		i;
	int		flag;
	char	**result;

	i = 0;
	while (tools->envp[i] != NULL)
	{
		flag = 0;
		result = ft_split(tools->envp[i], '=');
		flag = envp_addnode(result[0], result[1], &tools->envp_list);
		if (flag < 0)
			return (0);
		i++;
	}
	return (1);
}

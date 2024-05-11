/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:01:46 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/11 17:58:38 by irozhkov         ###   ########.fr       */
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
	node->name = ft_strdup(n);
	if (v)
		node->value = ft_strdup(v);
	else
		node->value = NULL;
	if (node->name == NULL)
	{
 		free(node->name);
		free(node->value);
		free(node);
		return (0);
	}
	node->next = NULL;
	node->prev = NULL;
	envp_addback(envp_list, node);
	return (1);
}

int	extract_key_value(const char *env_str, char **key, char **value)
{
	char	*equal_sign;
	int		key_len;

	equal_sign = ft_strchr(env_str, '=');
	if (equal_sign != NULL)
	{
		key_len = equal_sign - env_str;
		*key = (char *)malloc(sizeof(char) * (key_len + 1));
		*value = (char *)malloc(sizeof(char) * (ft_strlen(env_str) - key_len));
		if (*key == NULL || *value == NULL)
		{
			free(*key);
			free(*value);
			return (-1);
		}
		ft_strncpy(*key, env_str, key_len);
		(*key)[key_len] = '\0';
		ft_strcpy(*value, equal_sign + 1);
		return (0);
	}
	return (-1);
}

int	envp_reader(t_tools *tools)
{
	int		i;
	int		result;
	int		flag;
	char	*key;
	char	*value;

	i = 0;
	while (tools->envp[i] != NULL)
	{
		result = extract_key_value(tools->envp[i], &key, &value);
		if (result == 0)
		{
//			printf("---> key: %s\n", key);
//			printf("---> value: %s\n", value);
			flag = envp_addnode(key, value, &tools->envp_list);
			free(key);
			free(value);
			if (flag < 0)
				return (0);
		}
		i++;
	}
	return (1);
}

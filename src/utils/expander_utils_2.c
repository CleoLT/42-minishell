/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:13:50 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/31 21:51:34 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*expand_envpval(t_tools *tools, char *word)
{
	t_envp	*original_envp_list;
	char	*temp;

	original_envp_list = tools->envp_list;
	temp = NULL;
	while (tools->envp_list != NULL)
	{
		if ((ft_strncmp(word, tools->envp_list->name,
					ft_strlen(tools->envp_list->name)) == 0)
			&& (ft_strlen(word) == ft_strlen(tools->envp_list->name))
			&& tools->envp_list->value)
		{
			temp = (char *)malloc(sizeof(char)
					* (ft_strlen(tools->envp_list->value) + 1));
			ft_strcpy(temp, tools->envp_list->value);
			break ;
		}
		tools->envp_list = tools->envp_list->next;
	}
	free(word);
	tools->envp_list = original_envp_list;
	return (temp);
}

char	*expand_strword(t_tools *tools, char *s, int start, int end)
{
	char	*temp;
	int		i;

	temp = (char *)malloc(sizeof(char) * (end - start));
	if (!temp)
		return (NULL);
	i = 0;
	start += 1;
	while (start < end)
	{
		temp[i] = s[start];
		i++;
		start++;
	}
	temp[i] = '\0';
	if (ft_strlen(temp) == 0)
	{
		free(temp);
		return (NULL);
	}
	if (ft_strchr(temp, '\\') != NULL)
		return (expand_newline(temp));
	return (expand_envpval(tools, temp));
}

char	*expand_indx(t_tools *tools, char *s, int i)
{
	int			start_index;
	int			end_index;
	const char	*dollar_pos;
	const char	*e_pos;

	start_index = -1;
	end_index = -1;
	dollar_pos = &s[i];
	if (*dollar_pos == '$')
	{
		start_index = (int)(dollar_pos - s);
		e_pos = dollar_pos + 1;
		while ((ft_isspace(*e_pos) != 1) && (is_special(*e_pos) != -1))
			e_pos++;
		end_index = (int)(e_pos - s);
	}
	return (expand_strword(tools, s, start_index, end_index));
}

int	expander_envp_len(t_tools *tools, const char *word)
{
	t_envp	*original_envp_list;
	int		len;

	len = 0;
	original_envp_list = tools->envp_list;
	if (ft_strchr(word, '\\') != NULL)
		return (newline_len(word));
	else
	{
		while (tools->envp_list != NULL)
		{
			if (ft_strncmp(word, tools->envp_list->name,
					ft_strlen(tools->envp_list->name)) == 0)
			{
				len = ft_strlen(tools->envp_list->value);
				break ;
			}
			tools->envp_list = tools->envp_list->next;
		}
		tools->envp_list = original_envp_list;
	}
	return (len);
}

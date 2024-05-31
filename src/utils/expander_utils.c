/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:05:29 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/31 15:23:15 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	expander_value_len(t_tools *tools, const char *s, int start, int end)
{
	char	*word;
	int		i;
	int		j;
	int		len;

	len = 0;
	word = (char *)malloc(sizeof(char) * (end - start));
	if (!word)
		return (-1);
	i = 0;
	j = start;
	while (i < (end - start - 1))
	{
		j++;
		word[i] = s[j];
		i++;
	}
	word[i] = '\0';
	len = expander_envp_len(tools, word);
	free(word);
	return (len);
}

int	expander_len(t_tools *tools, const char *s, int i)
{
	int			len;
	int			start_index;
	int			end_index;
	const char	*dollar_pos;
	const char	*end_pos;

	len = 0;
	start_index = -1;
	end_index = -1;
	dollar_pos = &s[i];
	if (*dollar_pos == '$')
	{
		start_index = (int)(dollar_pos - s);
		end_pos = dollar_pos + 1;
		while ((ft_isspace(*end_pos) != 1) && *end_pos != '\0'
			&& *end_pos != '$')
			end_pos++;
		end_index = (int)(end_pos - s);
		len += expander_value_len(tools, s, start_index, end_index);
	}
	return (len);
}

int	dollar_len(const char *s, int i)
{
	int			start_index;
	int			end_index;
	const char	*dollar_pos;
	const char	*end_pos;

	start_index = -1;
	end_index = -1;
	dollar_pos = &s[i];
	if (*dollar_pos == '$')
	{
		start_index = (int)(dollar_pos - s);
		end_pos = dollar_pos + 1;
		while ((ft_isspace(*end_pos) != 1) && (is_special(*end_pos) != -1))
			end_pos++;
		end_index = (int)(end_pos - s);
	}
	return (end_index);
}

int	count_dollar(const char *s)
{
	int	counter;
	int	i;

	if (!s)
		return (0);
	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '$')
			counter++;
		i++;
	}
	return (counter);
}

int	is_dollar(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

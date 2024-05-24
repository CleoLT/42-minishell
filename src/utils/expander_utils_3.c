/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:26:14 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/24 13:45:43 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	expander_question_len(t_tools *tools)
{
	char	*temp;
	int		len;

	len = 0;
	temp = ft_itoa(tools->exit_code);
	len = ft_strlen(temp);
	free(temp);
	return (len);
}

char *expand_question(t_tools *tools)
{
	char	*temp;

	temp = ft_itoa(tools->exit_code);
	return (temp);
}

void	expander_addword(char *temp, char *temp_word, int *i)
{
	if (temp_word != NULL)
	{
		ft_chartochar(temp, temp_word, i);
		free(temp_word);
	}
}

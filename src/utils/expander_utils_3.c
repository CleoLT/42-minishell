/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:26:14 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/28 16:17:26 by irozhkov         ###   ########.fr       */
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

char *expand_special(t_tools *tools, char c, int *indx)
{
	char	*temp;

	temp = NULL;
	if (c == '?')
	{
		(*indx) += 2;
		return (expand_question(tools));
	}
	else
	{
		if (c == '\0')
		{
			temp = malloc(2 * sizeof(char));
			temp = "$";
			(*indx) += 1;
		}
		else if (c == '/')
        {
			temp = malloc(3 * sizeof(char));
   			temp = "$/";
            (*indx) += 2;
        }
	}
	return (temp);
}

void	expander_addword(char *temp, char *temp_word, int *i)
{
	if (temp_word != NULL)
	{
//		printf("---> expander_addword before i = %d\n", (*i));
		ft_chartochar(temp, temp_word, i);
//		printf("---> expander_addword after i = %d\n", (*i));
//		free(temp_word);
	}
}

int	is_special(char c)
{
	if (c == '=' || c == '@' || c == '#' || c == '-' || c == '+' || c == '{'
		|| c == '}' || c == '[' || c == ']' || c == '!' || c == '~' || c == '?'
		|| c == '%' || c == '^' || c == '=' || c == '*' || c == '/' || c == '$'
		|| c == ';' || c == '\0')
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:58:47 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/28 15:23:15 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	special_len(t_tools *tools, char c)
{
	if (c == '?')
		return (expander_question_len(tools));
	else if (c == '\0')
		return (2);
	else if (c == '/')
		return (2);
	return (0);
}

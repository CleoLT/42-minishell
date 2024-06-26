/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:11:01 by irozhkov          #+#    #+#             */
/*   Updated: 2024/04/09 15:53:49 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	spaces_handler(char *s, int i, t_token **lexer_list, int c)
{
	int	j;

	j = 0;
	while (ft_isspace(s[i + j]) == 1)
		j++;
	if (!token_addnode(ft_substr(s, i, j), 0, lexer_list, c))
		return (-1);
	return (j);
}

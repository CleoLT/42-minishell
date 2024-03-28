/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:19:47 by irozhkov          #+#    #+#             */
/*   Updated: 2024/03/27 19:23:02 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_arrdup(char **array)
{
	char	**tmp;
	size_t	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	tmp = ft_calloc(sizeof(char *), i + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		tmp[i] = ft_strdup(array[i]);
		if (!tmp[i])
		{
			free_arr(tmp);
			return (tmp);
		}
		i++;
	}
	return (tmp);
}

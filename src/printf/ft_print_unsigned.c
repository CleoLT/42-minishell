/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:38:49 by ale-tron          #+#    #+#             */
/*   Updated: 2024/02/14 19:37:10 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/ft_printf.h"

int	ft_print_unsigned(unsigned int nb)
{
	int		count;
	char	temp;

	count = 0;
	if (nb >= 10)
		count = ft_print_unsigned(nb / 10);
	if (count == -1)
		return (-1);
	temp = nb % 10 + '0';
	if (ft_print_char(temp) == -1)
		return (-1);
	return (count + 1);
}

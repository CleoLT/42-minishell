/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:39:21 by ale-tron          #+#    #+#             */
/*   Updated: 2024/02/14 19:37:10 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/ft_printf.h"

int	ft_print_int(int nb)
{
	int		count;
	char	temp;
	int		print;

	count = 0;
	if (nb == INT_MIN)
	{
		if (ft_print_string("-2147483648") == -1)
			return (-1);
		return (11);
	}
	if (nb < 0)
	{
		nb = -nb;
		if (ft_print_char('-') == -1)
			return (-1);
		count = 1;
	}
	if (nb >= 10)
		count += ft_print_int(nb / 10);
	if (count == -1)
		return (-1);
	temp = nb % 10 + '0';
	print = ft_print_char(temp);
	return (count + print);
}

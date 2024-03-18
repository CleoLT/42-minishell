/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:52:49 by ale-tron          #+#    #+#             */
/*   Updated: 2024/02/14 19:39:18 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/ft_printf.h"

static int	ft_long_hex(unsigned long num)
{
	int		count;
	int		hex;
	char	*base;

	base = "0123456789abcdef";
	count = 0;
	if (num >= 16)
		count = ft_long_hex(num / 16);
	if (count == -1)
		return (-1);
	hex = ft_print_char(base[num % 16]);
	return (count + hex);
}

int	ft_print_pointer(unsigned long address)
{
	int	count;

	if (!address)
		return (ft_print_string("0x0"));
	if (ft_print_string("0x") == -1)
		return (-1);
	count = ft_long_hex(address);
	if (count == -1)
		return (-1);
	return (count += 2);
}

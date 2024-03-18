/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:52:00 by ale-tron          #+#    #+#             */
/*   Updated: 2024/02/14 19:39:06 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/ft_printf.h"

int	ft_print_hex(unsigned int num, const char format)
{
	int		count;
	char	hex;
	int		print;

	count = 0;
	if (num >= 16)
		count = ft_print_hex(num / 16, format);
	if (count == -1)
		return (-1);
	if (num % 16 > 9)
		hex = num % 16 - 10 + format - 23;
	if (num % 16 < 10)
		hex = num % 16 + '0';
	print = ft_print_char(hex);
	return (count + print);
}

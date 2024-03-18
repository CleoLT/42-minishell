/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:56:01 by ale-tron          #+#    #+#             */
/*   Updated: 2024/02/14 19:37:52 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include "./libft.h"
# define FT_PRINTF_H

int	ft_printf(const char *str, ...);	
int	ft_print_char(int c);
int	ft_print_string(const char *src);
int	ft_print_hex(unsigned int num, const char format);
int	ft_print_pointer(unsigned long address);
int	ft_print_int(int nb);
int	ft_print_unsigned(unsigned int nb);

#endif

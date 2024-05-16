/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:58:10 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/05 15:47:43 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_limits(char *str)
{
    int i;
    int			sign;
	unsigned	long long 	num;

    i = 0;
    sign = 1;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -sign;
        i++;
    }
    num = 0;
    while (str[i] >= '0' && str[i] <= '9')
    {
        num = (str[i] - '0') + (num * 10);
        i++;
    }
	if (!ft_strncmp(str, "-9223372036854775808", 21))
		return ;
	if (num > LONG_MAX)
		exit(err_built("exit", str, ": numeric argument required", 255));
}

void	exec_exit(char *arg)
{
	int	num;

	num = ft_atoi(arg);
	num = num % 256;
	if (num < 0)
		exit(256 + num);
	else
		exit(num);
}

int	handle_syntax_error(char **arg, int *exit_code)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	j = 0;
	len = 0;
	if (arg[i] && !ft_strncmp(arg[i], "--", 3))
		i++;
	if (!arg[i])
		exit(*exit_code);
	if (arg[i][0] == '+' || arg[i][0] == '-') 
		j++;
	if (!arg[i][1])
		exit(err_built(arg[0], arg[i],": numeric argument required",  255));
	while (arg[i][j])
		if (!ft_isdigit(arg[i][j++]) || ++len >= 20)
			exit(err_built(arg[0], arg[i],": numeric argument required",  255));
	return (i);
}

void	ft_exit(char **arg, int *exit_code)
{
	int	i;

	ft_putendl_fd("exit", 2);
	i = handle_syntax_error(arg, exit_code);
	if (arg[i + 1])
	{
		*exit_code = err_built(arg[0], "", "too many arguments", 1);
		return ;
	}
	check_limits(arg[i]);
	exec_exit(arg[i]);
}
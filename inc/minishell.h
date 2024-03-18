/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:55:33 by ale-tron          #+#    #+#             */
/*   Updated: 2024/03/18 13:57:33 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <readline/readline.h>

# include "libft.h"
# include "macros.h"
# include "structures.h"


void	ft_error(char *arg, int exit_code);
void	lexer_token(char *line);

#endif

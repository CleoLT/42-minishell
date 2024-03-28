/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:55:33 by ale-tron          #+#    #+#             */
/*   Updated: 2024/03/28 15:12:10 by irozhkov         ###   ########.fr       */
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
# include "lexer.h"


void	ft_error(char *arg, int exit_code);
void	lexer_token(t_tools *tools, char *line);

/* envp_utils.c */
char	**ft_arrdup(char **array);

/* free_utils.c */
int		free_tools(t_tools *tools);
void	free_arr(char **array);

#endif

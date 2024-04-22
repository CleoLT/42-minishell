/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:55:33 by ale-tron          #+#    #+#             */
/*   Updated: 2024/04/22 13:24:32 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/errno.h>
# include <sys/param.h>
# include <readline/readline.h>

# include "libft.h"
# include "macros.h"
# include "structures.h"
# include "lexer.h"
# include "exec.h"
# include "expander.h"
# include "builtins.h"

void	lexer_token(t_tools *tools, char *line);

/* envp_utils.c */
char	**ft_arrdup(char **array);
char    **get_path_env(char **envp);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strcpy(char *dest, const char *src);

/* free_utils.c */
int		free_tools(t_tools *tools);
void	free_arr(char **array);

/* error.c */
void	ft_error(char *arg, int exit_code);
void	print_error(char *cmd, char *str, int exit_code);
int		ft_strerror(int exit_code);




#endif

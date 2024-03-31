/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:55:33 by ale-tron          #+#    #+#             */
/*   Updated: 2024/03/31 14:51:34 by cle-tron         ###   ########.fr       */
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
# include <readline/readline.h>

# include "libft.h"
# include "macros.h"
# include "structures.h"
# include "lexer.h"
# include "exec.h"

void	lexer_token(t_tools *tools, char *line);

/* envp_utils.c */
char	**ft_arrdup(char **array);
char    **get_path_env(char **envp);

/* free_utils.c */
int		free_tools(t_tools *tools);
void	free_arr(char **array);

/* error.c */
void	ft_error(char *arg, int exit_code);
void	print_error(char *cmd, char *str, int exit_code);
int		ft_strerror(int exit_code);




#endif

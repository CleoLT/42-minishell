/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:55:33 by ale-tron          #+#    #+#             */
/*   Updated: 2024/04/24 18:35:08 by cle-tron         ###   ########.fr       */
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
# include <fcntl.h>

# include "../readline/readline.h"
# include "../readline/history.h"
# include "libft.h"

# include "macros.h"
# include "structures.h"
# include "lexer.h"
# include "exec.h"
# include "expander.h"
# include "builtins.h"

int		signal_exit_code;

void	lexer_token(t_tools *tools, char *line);
void	ft_heredoc(t_cmd *cmd);

/* envp_utils.c */
char	**ft_arrdup(char **array);
char	**get_path_env(char **envp);
int		array_len(char **array);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strcpy(char *dest, const char *src);

/* free_utils.c */
int		free_tools(t_tools *tools);
void	free_arr(char **array);

/* error.c */
void	ft_error(char *arg, int exit_code);
void	ft_error_built(char *cmd, char *arg, int exit_code);
void	print_error(char *cmd, char *str, int exit_code);
int		ft_strerror(int exit_code); // esta creo que no sirve en nnguna parte 

/* signal.c */
void	ft_signals(int process, int *exit_code);
void	handle_sigquit(int sig);

/*commands faker*/
void	print_cdm_list(t_cmd *cmd);
void	cmd_faker(t_tools *tools, char *line);
#endif

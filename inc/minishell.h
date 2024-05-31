/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:55:33 by ale-tron          #+#    #+#             */
/*   Updated: 2024/05/31 15:08:12 by cle-tron         ###   ########.fr       */
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
# include <limits.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

# include "../readline/readline.h"
# include "../readline/history.h"
# include "libft.h"

# include "macros.h"
# include "structures.h"
# include "lexer.h"
# include "exec.h"
# include "expander.h"
# include "builtins.h"
# include "parser.h"

int		g_exit_code;

void	lexer_token(t_tools *tools, char *line);
int		ft_heredoc(t_cmd *cmd, int *exit_code);

/* init_tools.c */
int		tools_init(t_tools *tools, char **envp);
void	init_tools_loop(t_tools *tools);

/* envp_utils.c */
char	**ft_arrdup(char **array);

//char	**get_path_env(char **envp);
char	**get_path(t_tools tools);
int		array_len(char **array);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strcpy(char *dest, const char *src);

/* free_utils.c */
int		free_tools_loop(t_tools *tools, char *line);
void	free_envp(t_envp **envp_list);
void	free_tools(t_tools *tools);

/* free_utils2.c */
void	free_arr(char **array);
void	free_array_pt(char ***array);
void	free_exp_array(char ***array);

/* error.c */
void	ft_error(char *arg, int exit_code);
void	print_error(char *cmd, char *str, int exit_code);

/* error_return.c */
int		ft_strerror(int exit_code); // esta creo que no sirve en nnguna parte 
int		print_error_unset(char *cmd, char *arg); // esta en builts cambiar
int		err_built(char *cmd, char *arg, char *error, int exit_code);
int		perr_built(char *cmd, char *arg, int exit_code);
int		err_syntax(int type);

/* signal.c */
void	ft_signals(int process);
void	handle_sigquit(int sig);

/* print.c */
void	print_lexer_list(t_token *lexer_list);
void	print_cdm_list(t_cmd *cmd);

#endif

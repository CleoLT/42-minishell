/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:33:47 by irozhkov          #+#    #+#             */
/*   Updated: 2024/06/01 11:54:35 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/* envp.c */
int		envp_reader(t_tools *tools);
int		extract_key_value(const char *env_str, char **key, char **value);
int		envp_addnode(char *n, char *v, t_envp **envp_list);
void	envp_addback(t_envp **envp_list, t_envp *node);

/* token_reader.c */
int		check_token(int c);
int		token_handler(char *s, int i, t_token **lexer_list, int c);
int		token_addnode(char *s, int token, t_token **lexer_list, int c);
int		get_str(char *s, int i, t_token **lexer_list, int c);
int		token_reader(t_tools *tools);

/* lexer_utils.c */
char	*ft_strcat(char *dest, const char *src);
int		ft_doglue(t_token *current);
void	ft_gluenodes(t_tools *tools);
void	token_addback(t_token **lexer_list, t_token *node);
int		quotes_handler_extra(char *sub, char q, t_token **lexer_list, int c);

/* quotes.c */
int		quote_addnode(char *sub_str, char quote, t_token **lexer_list, int c);
void	quotes_str(const char *s, char *sub_str, int i);
int		quotes_handler(const char *s, int i, t_token **lexer_list, int c);
int		closed_quotes(const char *s, int i, int *counter, int quote);
int		count_quotes(const char *str);

/* spaces.c */
int		spaces_handler(char *s, int i, t_token **lexer_list, int c);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:33:47 by irozhkov          #+#    #+#             */
/*   Updated: 2024/03/30 13:26:47 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/* token_reader.c */
int		check_token(int c);
int		token_handler(char *s, int i, t_token **lexer_list);
int		token_addnode (char *s, int token, t_token **lexer_list);
int		get_str(char *s, int i, t_token **lexer_list);
int		token_reader(t_tools *tools);

/* lexer_utils.c */
void	token_addback(t_token **lexer_list, t_token *node);

/* quotes.c */
int		quotes_handler(char *s, int i, char quote, t_token **lexer_list);
int		closed_quotes(char *s, int i, int *counter, int quote);
int		count_quotes(char *str);

/* spaces.c */
int		spaces_handler(char *s, int i, t_token **lexer_list);

#endif

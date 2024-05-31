/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:34:29 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/31 19:02:27 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/* expander.c */
void	ft_chartochar(char *temp, char *temp_word, int *i);
int		expander_newlen(t_tools *tools, const char *s);
int		expander_reader(t_tools *tools);
void	expand_str(t_tools *tools, char *temp, const char *s);

/* expander_utils.c */
int		expander_value_len(t_tools *tools, const char *s, int start, int end);
int		expander_len(t_tools *tools, const char *s, int i);
int		dollar_len(const char *s, int i);
int		count_dollar(const char *s);
int		is_dollar(const char *s);

/* expander_utils_2.c */
char	*expand_envpval(t_tools *tools, char *word);
char	*expand_strword(t_tools *tools, char *s, int start, int end);
char	*expand_indx(t_tools *tools, char *s, int i);
int		expander_envp_len(t_tools *tools, const char *word);

/* expander_utils_3.c */
int		expander_question_len(t_tools *tools);
char	*expand_question(t_tools *tools);
char	*expand_special(t_tools *tools, char c, int *indx);
void	expander_addword(char *temp, char *temp_word, int *i);
int		is_special(char c);

/* expander_utils_4.c */
int		special_len(t_tools *tools, char c);
int		newline_len(const char *word);
char	*expand_newline(char *word);
char	*expand_special_other(char c, int *indx);

#endif

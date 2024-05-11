/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:34:29 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/11 16:17:08 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/* expander.c */
int		expander_newlen(t_tools *tools, const char *s);
int		expander_reader(t_tools *tools);

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

#endif

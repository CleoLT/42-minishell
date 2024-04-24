/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:34:29 by irozhkov          #+#    #+#             */
/*   Updated: 2024/04/20 16:47:30 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/* expander.c */
char		*expand_str(t_tools *tools, char *s, int indx[][2], int c);
char	*expand_indx(t_tools *tools, char *s, int c);
int			expander_reader(t_tools *tools);

/* expander_utils.c */
void	expand_word(t_tools *tools, char *s, int indx[][2], char *word);
int		len_expander(t_tools *tools, char *s, int i, int j);
int		newstr_len(t_tools *tools, char *s, int indx[][2], int c);
int		count_dollar(char *s);
int		is_dollar(char *s);

#endif

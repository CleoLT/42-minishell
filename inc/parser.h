/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <irozhkov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:14:35 by irozhkov          #+#    #+#             */
/*   Updated: 2024/05/29 15:38:37 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

int		ft_parser(t_tools *tools);
void	create_cmd_list(t_tools *tools, int *error);
void	malloc_and_errors_cmd(t_tools *tools, int *err);
/* parcer_utils.c */
void	ft_lexerdeltype(t_tools *tools, int del);
int		check_string(t_token *lex);

#endif

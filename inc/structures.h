/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:06:43 by ale-tron          #+#    #+#             */
/*   Updated: 2024/03/30 20:00:55 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_token
{
	int				type;
	char			*str;
	int				indx;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_envp
{
	char			*name;
	char			*value;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;

typedef struct s_tools
{
	char	**envp;
	char	*str;
	t_token	*lexer_list;
	t_envp	*envp_list;
}	t_tools;

#endif

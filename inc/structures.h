/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:06:43 by ale-tron          #+#    #+#             */
/*   Updated: 2024/03/29 14:24:06 by cle-tron         ###   ########.fr       */
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

typedef struct s_cmd
{
	char			**arg;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_tools
{
	char	**envp;
	char 	**path;
	char	*str;
	t_token	*lexer_list;
	t_cmd	*cmd;
//	int		fd_in;
//	int		fd_out;
	int		pipe_fd[2];
	pid_t	pid;
}	t_tools;

#endif

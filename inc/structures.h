/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:06:43 by ale-tron          #+#    #+#             */
/*   Updated: 2024/05/31 15:06:01 by cle-tron         ###   ########.fr       */
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

typedef struct s_cmd
{
	char			**arg;
	char			***infile;
	char			***outfile;
	int				ar;
	int				in;
	int				out;
	int				lexer_indx;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_tools
{
	char	**envp;
	char	**path;
	char	*str;
	t_token	*lexer_list;
	t_envp	*envp_list;
	t_cmd	*cmd;
	int		t_cmd_size;
	int		built_type;
	int		exit_code;
	int		stdin_fd;
	int		stdout_fd;
}	t_tools;

#endif

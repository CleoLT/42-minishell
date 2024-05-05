/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:06:43 by ale-tron          #+#    #+#             */
/*   Updated: 2024/05/05 12:13:04 by cle-tron         ###   ########.fr       */
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


typedef struct s_indx
{
	int				row;
	int				col;
	struct s_indx	*next;
	struct s_indx	*prev;
}	t_indx;

typedef struct s_cmd
{
	char			**arg;
	char			***infile;
	char			***outfile;
	int				*fd_in;
	int				*fd_out;
	struct s_cmd	*prev;
	struct s_cmd	*next;

}	t_cmd;

typedef struct s_tools
{
	char	**envp;
	char 	**path;
	char	*str;
	t_token	*lexer_list;
	t_envp	*envp_list;
	t_cmd	*cmd;
//	int		pipe_fd[2];
//	pid_t	*pid;
	int		t_cmd_size;
	int		built_type;
	int		exit_code;
}	t_tools;

#endif

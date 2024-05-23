/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:20:41 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/23 15:03:15 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		ft_is_builtin(char *arg);
int		exec_built(t_tools *tools, int type, t_cmd *cmd);
void	exec_simple_built(t_tools *tools, int built_type, t_cmd *cmd);
int		redirect_built(char ***infile, char ***outfile);

//ENV ECHO PWD
int		ft_env(t_envp *env);
int		ft_echo(char **arg);
int		ft_pwd(void);

//UNSET
int		ft_unset(t_envp **env, char **arg);
void	delete_env(t_envp **envp, char *arg);
int		print_error_unset(char *cmd, char *arg);

//EXPORT
int		ft_export(t_envp **envp, char **arg);
void	exec_export(char *name, char *value, int mode, t_envp **envp);
int		print_export(t_envp *envp);

//EXIT
void    ft_exit(char **arg, int *exit_code);

//CD
int		ft_cd(char **arg, t_tools *tools);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:20:41 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/02 11:55:53 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		ft_is_builtin(char *arg);
int		exec_built(t_tools *tools, int type, t_cmd *cmd);

//void	ft_cd(char **arg, t_tools *tools);
int		ft_unset(t_envp **env, char **arg);
void	delete_env(t_envp **envp, char *arg);
int		ft_export(t_envp **envp, char **arg);
int		ft_env(t_envp *env);

int	print_error_unset(char *cmd, char *arg);

#endif

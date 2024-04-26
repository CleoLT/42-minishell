/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:20:41 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/26 10:16:20 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	exec_built(t_tools *tools, int type, t_cmd *cmd);
void	ft_cd(char **arg, t_tools *tools);
void	ft_unset(t_envp **env, char **arg);

void    ft_env(t_envp *env);


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:20:41 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/26 14:00:47 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		exec_built(t_tools **tools, int type, t_cmd *cmd);
//void	ft_cd(char **arg, t_tools *tools);
int	ft_unset(t_envp **env, char **arg);

int    ft_env(t_envp *env);

#endif

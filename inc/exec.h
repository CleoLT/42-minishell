/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:41:52 by cle-tron          #+#    #+#             */
/*   Updated: 2024/04/17 14:21:46 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H


void    exec_cmd(t_tools *tools, t_cmd *cmd);
void	execute(t_tools *tools);
void	ft_cd(char *dir);

#endif

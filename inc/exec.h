/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:41:52 by cle-tron          #+#    #+#             */
/*   Updated: 2024/05/31 15:05:17 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void	exec_cmd(t_tools *tools, t_cmd *cmd);
void	execute(t_tools *tools);

int		redirect_infile(char ***infile);
int		redirect_outfile(char ***outfile);
void	redirect_stdin_out(t_tools *tools);

char	*find_path(t_tools *tools, t_cmd *cmd);
int		is_directory(char *str);
#endif

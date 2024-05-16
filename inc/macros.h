/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:59:09 by ale-tron          #+#    #+#             */
/*   Updated: 2024/05/16 16:39:09 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MACROS_H
# define MACROS_H

//TOKENS

# define PIPE		1 // |
# define INPUT		2 // <
# define OUTPUT		3 // >
# define HEREDOC	4 // <<
# define APPEND		5 // >>
# define STRING		6
# define STRINGD	7
# define STRINGS	8
# define SPACE2		0 // I change the name of this macro because isn't compatible with readline library

# define MAXARGS	10

//PIPES
# define READ_END	0
# define WRITE_END	1

//BUILTINS
# define ECH		1
# define CD			2
# define PWD		3
# define EXPORT		4
# define UNSET		5
# define ENV		6
# define EXIT		7

//PROCESS
# define PROCESS_OFF	0
# define PROCESS_ON		1
# define PROCESS_HD		2

//EXPORT MODE
# define NAME_ONLY		0
# define REPLACE_MODE	1
# define APPEND_MODE	2


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:59:09 by ale-tron          #+#    #+#             */
/*   Updated: 2024/04/10 16:48:03 by irozhkov         ###   ########.fr       */
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
# define SPACE		0

# define MAXARGS	10

//PIPES
# define READ_END	0
# define WRITE_END	1

//BUILTINS
# define ECHO		1
# define CD			2
# define PWD		3
# define EXPORT		4
# define UNSET		5
# define ENV		6
# define EXIT		7

#endif

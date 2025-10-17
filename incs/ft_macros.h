/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_macros.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:46:44 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/17 21:37:13 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MACROS_H
# define FT_MACROS_H

// POSIX whitespaces
# define WS_SPACE		' '
# define WS_HTAB		'\t'
# define WS_NLINE		'\n'
# define WS_VTAB		'\v'
# define WS_FFEED		'\f'
# define WS_RETURN		'\r'
# define WS_POSIX	" \t\n\v\f\r"

// Shell command operators
# define CMD_AND        "&&"
# define CMD_OR         "||"
# define CMD_PIPE       "|"
# define CMD_HEREDOC    "<<"
# define CMD_IN         "<"
# define CMD_OUT        ">"
# define CMD_OUT_APPEND ">>"
# define CMD_ALL "&|<>"

// Error messages
# define ERR_SYNTAX "Syntax error\n"

#endif
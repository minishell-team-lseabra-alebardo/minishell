/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_macros.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:46:44 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/11 14:38:30 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MACROS_H
# define FT_MACROS_H

# define PGM_NAME "minishell"

// Colors
# define ORANGE		"\033[38;5;208m"
# define BLUE_GULF	"\e[38;5;33m"
# define WHITE		"\033[38;5;255m"
# define RESET		"\033[0m"

// Internal functions return
# define ERROR		-1
# define SUCCESS	0

// POSIX whitespaces
# define WS_SPACE		' '
# define WS_HTAB		'\t'
# define WS_NLINE		'\n'
# define WS_VTAB		'\v'
# define WS_FFEED		'\f'
# define WS_RETURN		'\r'
# define WS_POSIX		" \t\n\v\f\r"

// Shell command operators
# define CMD_AND		"&&"
# define CMD_OR			"||"
# define CMD_PIPE		"|"
# define CMD_HEREDOC	"<<"
# define CMD_IN			"<"
# define CMD_OUT		">"
# define CMD_OUT_APPEND	">>"
# define CMD_ALL		"&|<>"

// HEREDOC
# define HEREDOC_PREFIX	"> "
# define HEREDOC_WARN	"warning: here-document delimited by end-of-file"

// Error messages
# define ERR_GENERIC		"Error\n"
# define ERR_SYNTAX			"Syntax error\n"
# define ERR_NO_PERMISSION	"Permission denied\n"
# define ERR_CMD_NOT_FOUND	"command not found\n"
# define ERR_BAD_FD			"Bad file descriptor\n"
# define ERR_TOO_MANY_ARGS	"too many arguments\n"
# define ERR_INV_ID			"not a valid identifier\n"

// Exit status code
# define EXIT_CANNOT_EXEC	126
# define EXIT_NOT_FOUND		127

# define MAX_PROCESSES	1024

//Builtins
# define EXP_PREFIX	"declare -x "

#endif
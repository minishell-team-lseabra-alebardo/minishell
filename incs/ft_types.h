/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:56:36 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/05 22:59:29 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPES_H
# define FT_TYPES_H

typedef struct sigaction	t_sigaction;

/**
 * @struct s_cmd
 * @brief Represents a single command node in the minishell execution flow.
 *
 * Stores all necessary information to execute a command, including its name,
 * arguments, input/output redirections, and logical relationships with other
 * commands. Typically used to build a linked list or pipeline of commands.
 *
 * Typical usage:
 *  - Parsing user input into a linked list of `t_cmd` structures.
 *  - Executing commands sequentially or in pipelines.
 *  - Managing I/O redirections and logical operators ("&&", "||", "|").
 *
 * @var s_cmd::ms_envp
 *   Pointer to a copy of `envp` with any modified environment variables.
 * @var s_cmd::cmd
 *   The command name (e.g., "ls", "grep", "cat").
 * @var s_cmd::args
 *   Array of arguments for the command.
 * @var s_cmd::infile
 *   Input redirection file ("<"), NULL if not used.
 * @var s_cmd::outfile
 *   Output redirection file (">" or ">>"), NULL if not used.
 * @var s_cmd::prev_op
 *   Operator linking to the previous command ("|", "&&", "||"), NULL if none.
 * @var s_cmd::lst_stat
 *   Exit status of the last executed command, useful for logical operators.
 * @var s_cmd::level
 *   Execution depth or grouping level, for subshells or parentheses.
 * @var s_cmd::next
 *   Pointer to the next command in the linked list.
 */

typedef struct s_redir
{
	char			*type;
	char			*filename;
	char			*fd_from;
	int				fd_to;
	struct s_redir	*next;
}			t_redir;

typedef struct s_cmd
{
	char			**ms_envp;
	char			*prev_op;
	char			**args;
	int				infile;
	int				outfile;
	int				**dup2_backup;
	t_redir			*redir_ll;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	char	**ms_envp;
	int		pexit;
	char	*prompt;
	char	*line;
	char	**split_line;
	t_cmd	*cmd_ll;
	pid_t	pid_arr[MAX_PROCESSES];
}			t_data;
#endif
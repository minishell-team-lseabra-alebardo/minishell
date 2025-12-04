/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:07:14 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/04 12:21:36 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

/**
 * @brief Applies an input redirection to a command.
 *
 * This function handles input redirections of type CMD_IN or CMD_HEREDOC.
 * For heredocs, the file descriptor produced earlier (rdr->fd_to) is assigned
 * directly to the command's infile. For standard input redirections, the
 * specified filename is opened in read-only mode. 
 *
 * If the command already has an infile open (greater than STDERR_FILENO),
 * it is closed before applying the new redirection. Errors opening a file
 * set the status to EXIT_FAILURE and print an appropriate error message.
 *
 * @param cmd Pointer to the command structure that will receive the infile.
 * @param rdr Pointer to the redirection structure describing the redirection.
 * @param status Pointer to an integer storing the overall redirection status.
 */
static void	ft_apply_infile(t_cmd *cmd, t_redir *rdr, int *status)
{
	if (ft_is_op(rdr->type, CMD_HEREDOC))
	{
		if (cmd->infile > STDERR_FILENO)
			close(cmd->infile);
		cmd->infile = rdr->fd_to;
	}
	else if (ft_is_op(rdr->type, CMD_IN))
	{
		if (cmd->infile > STDERR_FILENO)
			close(cmd->infile);
		cmd->infile = open(rdr->filename, O_RDONLY);
		if (cmd->infile < 0)
		{
			*status = EXIT_FAILURE;
			ft_puterror(NULL, rdr->filename, NULL);
		}
	}
}

/**
 * @brief Resolves the source file descriptor for a numeric redirection.
 *
 * Used for cases like `2>` where an explicit FD may be provided. If @p fd_from
 * is not NULL, it is converted to an integer. If it is NULL, the function
 * returns STDIN_FILENO as a neutral default to indicate that no FD was
 * specified, letting the caller apply its own default behavior.
 *
 * @param fd_from String containing the FD before the redirection operator,
 *        or NULL if none was given.
 * @return The resolved file descriptor.
 */
static int	ft_handle_fd_from(char *fd_from)
{
	int	res;

	if (fd_from)
		res = ft_str_to_fd(fd_from);
	else
		res = STDIN_FILENO;
	return (res);
}

/**
 * @brief Opens an output file according to its redirection type.
 *
 * This function opens the output file with the appropriate flags based on
 * the redirection operator:
 * - CMD_OUT uses truncate mode (">")
 * - CMD_OUT_APPEND uses append mode (">>")
 *
 * The file is created if it does not exist (permission 0644).
 *
 * @param type The redirection operator type.
 * @param filename The name of the file to open.
 * @return The file descriptor on success, or -1 on failure.
 */
static int	ft_open_outfile(char *type, char *filename)
{
	int	fd;

	fd = -1;
	if (ft_is_op(type, CMD_OUT))
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_is_op(type, CMD_OUT_APPEND))
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

/**
 * @brief Applies an output redirection to a command.
 *
 * This function handles output redirections (CMD_OUT or CMD_OUT_APPEND).
 * It creates or opens the output file via ft_open_outfile(). If the file
 * cannot be opened, an error is printed and the redirection status is set.
 *
 * The redirection may specify an alternate source file descriptor (fd_from),
 * which is resolved with ft_handle_fd_from(). If this FD is valid and greater
 * than STDIN, ft_dup2_backup_close() is used to duplicate the new outfile
 * onto it and record the operation for possible restoration (when the command
 * is executed in the parent process).
 *
 * If no explicit fd_from is provided, the command's existing outfile is closed
 * (if necessary) and replaced with the newly opened file descriptor.
 *
 * @param cmd Pointer to the command structure receiving the outfile.
 * @param rdr Pointer to the redirection structure.
 * @param status Pointer to an integer tracking redirection success or failure.
 */
static void	ft_apply_outfile(t_cmd *cmd, t_redir *rdr, int *status)
{
	int	fd_from;
	int	fd;

	fd = ft_open_outfile(rdr->type, rdr->filename);
	if (fd < 0)
	{
		*status = ft_puterror_ret(NULL, rdr->filename, NULL, EXIT_FAILURE);
		return ;
	}
	fd_from = ft_handle_fd_from(rdr->fd_from);
	if (fd_from > STDIN_FILENO)
		ft_dup2_backup_close(fd, fd_from, cmd);
	else if (fd_from < 0 || fd_from >= 1024)
	{
		*status = ft_puterror_ret(NULL, rdr->fd_from, ERR_BAD_FD, EXIT_FAILURE);
		return ;
	}
	else
	{
		if (cmd->outfile > STDERR_FILENO)
			close(cmd->outfile);
		cmd->outfile = fd;
	}
}

/**
 * @brief Applies all input/output redirections belonging to a command.
 *
 * This function iterates through the command's redirection linked list
 * (cmd->redir_ll) and applies each redirection in order. It supports:
 *
 * - CMD_HEREDOC and CMD_IN through ft_apply_infile()
 * - CMD_OUT and CMD_OUT_APPEND through ft_apply_outfile()
 *
 * If any redirection fails (status != EXIT_SUCCESS), processing stops early
 * and the failure status is returned. Otherwise, EXIT_SUCCESS is returned
 * once all redirections have been applied.
 *
 * @param cmd Pointer to the command whose redirections will be applied.
 * @return EXIT_SUCCESS if all redirections were applied successfully,
 *         EXIT_FAILURE otherwise.
 */
int	ft_apply_redirs(t_cmd *cmd)
{
	t_redir	*cur_rdr;
	int		status;

	cur_rdr = cmd->redir_ll;
	status = EXIT_SUCCESS;
	while (cur_rdr)
	{
		if (ft_is_op(cur_rdr->type, CMD_HEREDOC)
			|| ft_is_op(cur_rdr->type, CMD_IN))
		{
			ft_apply_infile(cmd, cur_rdr, &status);
		}
		else if (ft_is_op(cur_rdr->type, CMD_OUT_APPEND)
			|| ft_is_op(cur_rdr->type, CMD_OUT))
		{
			ft_apply_outfile(cmd, cur_rdr, &status);
		}
		cur_rdr = cur_rdr->next;
		if (status != EXIT_SUCCESS)
			break ;
	}
	return (status);
}

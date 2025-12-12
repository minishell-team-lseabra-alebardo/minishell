/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:07:14 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/12 15:13:30 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

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

static int	ft_handle_fd_from(char *fd_from)
{
	int	res;

	if (fd_from)
		res = ft_str_to_fd(fd_from);
	else
		res = STDIN_FILENO;
	return (res);
}

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

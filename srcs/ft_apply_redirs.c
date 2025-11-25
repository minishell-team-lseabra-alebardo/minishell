/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:07:14 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/25 12:29:51 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_apply_heredoc(t_cmd *cmd, t_redir *rdr)
{
	if (ft_is_op(rdr->type, CMD_HEREDOC))
	{
		if (cmd->infile > STDERR_FILENO)
			close(cmd->infile);
		cmd->infile = rdr->fd_to;
	}
}

static void	ft_apply_infile(t_cmd *cmd, t_redir *rdr)
{
	if (ft_is_op(rdr->type, CMD_IN))
	{
		if (cmd->infile > STDERR_FILENO)
			close(cmd->infile);
		cmd->infile = open(rdr->filename, O_RDONLY);
		if (cmd->infile < 0)
			ft_puterror_exit(NULL, rdr->filename, NULL, EXIT_FAILURE);
	}
}

static void	ft_apply_outfile(t_cmd *cmd, t_redir *rdr)
{
	int	fd;
	int	fd_from;

	if (rdr->fd_from)
		fd_from = ft_str_to_fd(rdr->fd_from);
	else
		fd_from = 0;
	if (ft_is_op(rdr->type, CMD_OUT))
	{
		fd = open(rdr->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			ft_puterror_exit(NULL, rdr->filename, NULL, EXIT_FAILURE);
		if (fd_from > STDIN_FILENO)
			ft_dup2_close(fd, fd_from);
		else if (fd_from < 0)
			ft_puterror_exit(NULL, rdr->fd_from, ERR_BAD_FD, EXIT_FAILURE);
		else
		{
			if (cmd->outfile > STDERR_FILENO)
				close(cmd->outfile);
			cmd->outfile = fd;
		}
	}
}

static void	ft_apply_append_outfile(t_cmd *cmd, t_redir *rdr)
{
	int	fd;
	int	fd_from;

	if (rdr->fd_from)
		fd_from = ft_str_to_fd(rdr->fd_from);
	else
		fd_from = 0;
	if (ft_is_op(rdr->type, CMD_OUT_APPEND))
	{
		fd = open(rdr->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			ft_puterror_exit(NULL, rdr->filename, NULL, EXIT_FAILURE);
		if (fd_from > STDIN_FILENO)
			ft_dup2_close(fd, fd_from);
		else if (fd_from < 0)
			ft_puterror_exit(NULL, rdr->fd_from, ERR_BAD_FD, EXIT_FAILURE);
		else
		{
			if (cmd->outfile > STDERR_FILENO)
				close(cmd->outfile);
			cmd->outfile = fd;
		}
	}
}

void	ft_apply_redirs(t_cmd *cmd)
{
	t_redir	*cur_redir;

	cur_redir = cmd->redir_ll;
	while (cur_redir)
	{
		ft_apply_heredoc(cmd, cur_redir);
		ft_apply_infile(cmd, cur_redir);
		ft_apply_outfile(cmd, cur_redir);
		ft_apply_append_outfile(cmd, cur_redir);
		cur_redir = cur_redir->next;
	}
}

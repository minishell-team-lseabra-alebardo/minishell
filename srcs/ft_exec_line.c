/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:48:00 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/04 18:29:01 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_apply_infile(t_cmd *cmd, t_redir *redir)
{
	if (ft_is_op(redir->type, CMD_HEREDOC))
	{
		if (cmd->infile > STDERR_FILENO)
			close(cmd->infile);
		cmd->infile = redir->fd_to;
	}
	else if (ft_is_op(redir->type, CMD_IN))
	{
		if (cmd->infile > STDERR_FILENO)
			close(cmd->infile);
		cmd->infile = open(redir->filename, O_RDONLY);
		if (cmd->infile < 0)
		{
			perror(strerror(errno));
			exit(127);
		}
	}
}

static void	ft_apply_outfile(t_cmd *cmd, t_redir *redir)
{
	if (ft_is_op(redir->type, CMD_OUT))
	{
		if (cmd->infile > STDERR_FILENO)
			close(cmd->infile);
		cmd->infile = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->infile < 0)
		{
			perror(strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else if (ft_is_op(redir->type, CMD_OUT_APPEND))
	{
		if (cmd->infile > STDERR_FILENO)
			close(cmd->infile);
		cmd->infile = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->infile < 0)
		{
			perror(strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
}

static void	ft_apply_redirs(t_cmd *cmd)
{
	t_redir	*cur_redir;

	cur_redir = cmd->redir_ll;
	while (cur_redir)
	{
		ft_apply_outfile(cmd, cur_redir);
		ft_apply_outfile(cmd, cur_redir);
		cur_redir = cur_redir->next;
	}
}

static int	ft_exec_child(t_cmd *cur_cmd)
{
	ft_apply_redirs(cur_cmd);
}

void	ft_exec_line(t_data *dt)
{
	t_cmd	*cur_cmd;
	int		i;

	i = 0;
	while (cur_cmd)
	{
		dt->pid_arr[i] = fork();
		if (dt->pid_arr[i] == 0)
			ft_exec_child(cur_cmd);
		cur_cmd = cur_cmd->next;
		if (!ft_is_op(cur_cmd->prev_op, CMD_PIPE))
			waitpid(dt->pid_arr[i]);
		i++;
	}
}

// MS_PATH
// args[0] = "minishell"
// args[1] = "()"
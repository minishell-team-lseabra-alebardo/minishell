/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:46:07 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/10 15:28:03 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_close_redir_files(t_redir *redir_ll)
{
	t_redir	*cur_redir;

	if (!redir_ll)
		return ;
	cur_redir = redir_ll;
	while (cur_redir)
	{
		if (cur_redir->fd_to > STDERR_FILENO)
		{
			close(cur_redir->fd_to);
			cur_redir->fd_to = -1;
		}
		cur_redir = cur_redir->next;
	}
}

void	ft_close_unused_fds(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->infile > STDERR_FILENO)
		{
			close(cmd->infile);
			cmd->infile = -1;
		}
		if (cmd->outfile > STDERR_FILENO)
		{
			close(cmd->outfile);
			cmd->infile = -1;
		}
		ft_close_redir_files(cmd->redir_ll);
		cmd = cmd->next;
	}
}

void	ft_close_cmd_files(t_cmd *cmd)
{
	if (cmd->infile > STDERR_FILENO)
	{
		close(cmd->infile);
		cmd->infile = -1;
	}
	if (cmd->outfile > STDERR_FILENO)
	{
		close(cmd->outfile);
		cmd->infile = -1;
	}
	ft_close_redir_files(cmd->redir_ll);
}

void	ft_wait_all_pids(t_data *dt)
{
	pid_t	cur_pid;
	int		lst_stat;
	int		i;

	i = 0;
	cur_pid = dt->pid_arr[i];
	while (cur_pid != 0)
	{
		waitpid(cur_pid, &lst_stat, 0);
		i++;
		cur_pid = dt->pid_arr[i];
	}
	if (ft_get_status(0, false) != 130)
		ft_get_status(WEXITSTATUS(lst_stat), true);
}

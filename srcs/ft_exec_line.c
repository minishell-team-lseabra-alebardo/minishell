/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:48:00 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/07 14:12:13 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_exec_cmd(t_cmd *cmd)
{
	char	*path;
	int		status;

	path = NULL;
	status = ft_resolve_cmd_path(cmd->args[0], &path);
	if (status != EXIT_SUCCESS)
		perror_exit(cmd->args[0], status);
}

static void	ft_exec_child(t_cmd *cmd)
{
	ft_close_unused_fds(cmd->next);
	ft_apply_redirs(cmd);
}

static void	ft_skip_based_on_stat(t_cmd **cmd, pid_t prev_pid)
{
	pid_t	lst_blk_st;

	waitpid(prev_pid, &lst_blk_st, 0);
	if (WIFEXITED(lst_blk_st))
	{
		if ((WEXITSTATUS(lst_blk_st) == 0
				&& ft_is_op((*cmd)->prev_op, CMD_OR))
			|| (WEXITSTATUS(lst_blk_st) != 0
				&& ft_is_op((*cmd)->prev_op, CMD_AND)))
		{
			while (*cmd && ft_is_op((*cmd)->prev_op, CMD_PIPE))
			{
				if ((*cmd)->infile > STDERR_FILENO)
					close((*cmd)->infile);
				if ((*cmd)->outfile > STDERR_FILENO)
					close((*cmd)->outfile);
				*cmd = (*cmd)->next;
			}
		}
	}
}

void	ft_exec_line(t_data *dt)
{
	t_cmd	*cur_cmd;
	int		i;

	cur_cmd = dt->cmd_ll;
	i = 0;
	while (cur_cmd)
	{
		dt->pid_arr[i] = fork();
		if (dt->pid_arr[i] == 0)
			ft_exec_child(cur_cmd);
		if (cur_cmd->infile > STDERR_FILENO)
			close(cur_cmd->infile);
		if (cur_cmd->outfile > STDERR_FILENO)
			close(cur_cmd->outfile);
		cur_cmd = cur_cmd->next;
		if (cur_cmd && !ft_is_op(cur_cmd->prev_op, CMD_PIPE))
			ft_skip_based_on_stat(&cur_cmd, dt->pid_arr[i]);
		i++;
	}
}

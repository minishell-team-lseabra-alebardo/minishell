/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:48:00 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/21 18:14:08 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_skip_based_on_stat(t_cmd **cmd, pid_t prev_pid, int *lst_stat)
{
	pid_t	lst_proc_st;

	waitpid(prev_pid, &lst_proc_st, 0);
	if (WIFEXITED(lst_proc_st))
	{
		*lst_stat = WEXITSTATUS(lst_proc_st);
		while (*cmd && ((*lst_stat == 0 && ft_is_op((*cmd)->prev_op, CMD_OR))
				|| (*lst_stat != 0 && ft_is_op((*cmd)->prev_op, CMD_AND))))
		{
			*cmd = (*cmd)->next;
			while (*cmd && ft_is_op((*cmd)->prev_op, CMD_PIPE))
			{
				ft_close_cmd_files(*cmd);
				*cmd = (*cmd)->next;
			}
		}
	}
}

static void	ft_exec_child(t_data * dt, t_cmd *cmd)
{
	ft_close_unused_fds(cmd->next);
	ft_apply_redirs(cmd);
	if (ft_is_builtin(cmd->args[0]))
		ft_exec_builtin(dt, cmd);
	else
		ft_exec_cmd(cmd, dt->ms_envp);
}

void	ft_exec_line(t_data *dt)
{
	t_cmd	*cur_cmd;
	int		i;

	cur_cmd = dt->cmd_ll;
	i = 0;
	while (cur_cmd)
	{
		dt->pexit = 0;
		if (ft_is_in_pipeline(cur_cmd))
			dt->pexit = 1;
		if (ft_is_builtin(cur_cmd->args[0]) && !ft_is_in_pipeline(cur_cmd))
		{
			ft_exec_builtin(dt, cur_cmd);
			cur_cmd = cur_cmd->next;
			continue ;
		}
		dt->pid_arr[i] = fork();
		if (dt->pid_arr[i] == 0)
			ft_exec_child(dt, cur_cmd);
		ft_close_cmd_files(cur_cmd);
		cur_cmd = cur_cmd->next;
		if (cur_cmd && !ft_is_op(cur_cmd->prev_op, CMD_PIPE))
			ft_skip_based_on_stat(&cur_cmd, dt->pid_arr[i], &dt->lst_stat);
		i++;
	}
	ft_wait_all_pids(dt);
	ft_cleanup_line(dt);
}

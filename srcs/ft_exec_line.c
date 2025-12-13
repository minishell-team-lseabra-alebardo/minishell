/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:48:00 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/13 21:24:41 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_skip_pipeline(t_cmd **cmd)
{
	*cmd = (*cmd)->next;
	while (*cmd && ft_is_op((*cmd)->prev_op, CMD_PIPE))
	{
		ft_close_cmd_files(*cmd);
		*cmd = (*cmd)->next;
	}
}

static void	ft_skip_based_on_stat(t_cmd **cmd, pid_t prev_pid)
{
	int		lst_proc_st;

	lst_proc_st = 0;
	if (!(*cmd))
		return ;
	else if (!(*cmd)->next || ft_is_op((*cmd)->next->prev_op, CMD_PIPE))
	{
		*cmd = (*cmd)->next;
		return ;
	}
	if (!ft_is_parent_bltn((*cmd)->args[0]))
	{
		waitpid(prev_pid, &lst_proc_st, 0);
		if (WIFEXITED(lst_proc_st))
			ft_get_status(WEXITSTATUS(lst_proc_st), true);
	}
	*cmd = (*cmd)->next;
	while (*cmd && ((ft_get_status(0, false) == 0
				&& ft_is_op((*cmd)->prev_op, CMD_OR))
			|| (ft_get_status(0, false) != 0
				&& ft_is_op((*cmd)->prev_op, CMD_AND))))
	{
		ft_skip_pipeline(cmd);
	}
}

static void	ft_treat_child(t_data *dt, t_cmd *cur_cmd, int pid_pos)
{
	int	status;

	dt->pid_arr[pid_pos] = fork();
	if (dt->pid_arr[pid_pos] == 0)
		ft_exec_child(dt, cur_cmd);
	else if (!cur_cmd->next)
	{
		waitpid(dt->pid_arr[pid_pos], &status, 0);
		if (WIFEXITED(status))
			ft_get_status((unsigned char)WEXITSTATUS(status), true);
	}
}

void	ft_exec_line(t_data *dt)
{
	t_cmd	*cur_cmd;
	int		i;

	cur_cmd = dt->cmd_ll;
	i = -1;
	while (cur_cmd && i < MAX_PROCESSES)
	{
		ft_args_treatment(cur_cmd->args, dt, 1);
		if (cur_cmd->args[0][0] == '(')
			ft_get_status(ft_subshell(cur_cmd->args, dt->ms_envp), true);
		else if (ft_is_parent_bltn(cur_cmd->args[0]) && !ft_is_in_pipeline(cur_cmd))
			ft_get_status(ft_exec_builtin(dt, cur_cmd), true);
		else
		{
			i++;
			ft_treat_child(dt, cur_cmd, i);
		}
		ft_close_cmd_files(cur_cmd);
		if (ft_get_status(0, false) == 130)
			break ;
		ft_skip_based_on_stat(&cur_cmd, dt->pid_arr[i]);
		dt->last_status = ft_get_status(0, false);
	}
	ft_wait_all_pids(dt);
	ft_cleanup_line(dt);
}

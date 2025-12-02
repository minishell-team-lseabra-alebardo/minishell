/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:48:00 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/02 17:11:29 by alebarbo         ###   ########.fr       */
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

static void	ft_skip_based_on_stat(t_cmd **cmd, pid_t prev_pid, int *lst_stat)
{
	pid_t	lst_proc_st;

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
			*lst_stat = WEXITSTATUS(lst_proc_st);
	}
	*cmd = (*cmd)->next;
	while (*cmd && ((*lst_stat == 0 && ft_is_op((*cmd)->prev_op, CMD_OR))
			|| (*lst_stat != 0 && ft_is_op((*cmd)->prev_op, CMD_AND))))
	{
		ft_skip_pipeline(cmd);
	}
}

static void	ft_exec_child(t_data *dt, t_cmd *cmd)
{
	int	status;

	ft_close_unused_fds(cmd->next);
	status = ft_apply_redirs(cmd);
	if (status != EXIT_SUCCESS)
	{
		ft_close_cmd_files(cmd);
		exit(status);
	}
	ft_dup2_close(cmd->infile, STDIN_FILENO);
	ft_dup2_close(cmd->outfile, STDOUT_FILENO);
	if (ft_is_builtin(cmd->args[0]))
	{
		status = ft_exec_builtin(dt, cmd);
		ft_close_cmd_files(cmd);
		exit(status);
	}
	else
		ft_exec_cmd(cmd, dt->ms_envp, dt->lst_stat);
}

void	ft_exec_line(t_data *dt)
{
	t_cmd	*cur_cmd;
	int		i;

	cur_cmd = dt->cmd_ll;
	i = 0;
	while (cur_cmd)
	{
		ft_args_treatment(cur_cmd->args, dt, 1);
		if (ft_is_parent_bltn(cur_cmd->args[0]) && !ft_is_in_pipeline(cur_cmd))
			dt->lst_stat = ft_exec_builtin(dt, cur_cmd);
		else
		{
			dt->pid_arr[i] = fork();
			if (dt->pid_arr[i] == 0)
				ft_exec_child(dt, cur_cmd);
			i++;
		}
		ft_close_cmd_files(cur_cmd);
		ft_skip_based_on_stat(&cur_cmd, dt->pid_arr[i], &dt->lst_stat);
	}
	ft_wait_all_pids(dt);
	ft_cleanup_line(dt);
}

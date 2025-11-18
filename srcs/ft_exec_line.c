/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:48:00 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/18 16:19:04 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_handle_path_failure(t_cmd *cmd, int status)
{
	char	*msg;

	ft_close_cmd_files(cmd);
	if (status == EXIT_NOT_FOUND)
		msg = ERR_CMD_NOT_FOUND;
	else if (status == EXIT_CANNOT_EXEC)
		msg = ERR_NO_PERMISSION;
	else
		msg = ERR_GENERIC;
	ft_puterror_exit(cmd->args[0], msg, status);
}

void	ft_exec_cmd(t_cmd *cmd, char **ms_envp)
{
	char	*path;
	int		status;

	path = NULL;
	ft_args_treatment(cmd->args, ms_envp, 1);
	if (ft_prepare_subshell(ms_envp, cmd, &path))
		status = EXIT_SUCCESS;
	else
		status = ft_resolve_cmd_path(cmd->args[0], &path);
	if (status != EXIT_SUCCESS)
		ft_handle_path_failure(cmd, status);
	ft_dup2_close(cmd->infile, STDIN_FILENO);
	ft_dup2_close(cmd->outfile, STDOUT_FILENO);
	execve(path, cmd->args, ms_envp);
	free(path);
	ft_close_cmd_files(cmd);
	perror("execve");
}

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
		{
			ft_close_unused_fds(cur_cmd->next);
			ft_apply_redirs(cur_cmd);
			ft_exec_cmd(cur_cmd, dt->ms_envp);
		}
		ft_close_cmd_files(cur_cmd);
		cur_cmd = cur_cmd->next;
		if (cur_cmd && !ft_is_op(cur_cmd->prev_op, CMD_PIPE))
			ft_skip_based_on_stat(&cur_cmd, dt->pid_arr[i], &dt->lst_stat);
		i++;
	}
	ft_wait_all_pids(dt);
	ft_cleanup_line(dt);
}

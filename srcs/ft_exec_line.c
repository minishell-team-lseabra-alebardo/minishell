/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:48:00 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/08 22:44:25 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

/**
 * @brief Skips all commands in the current pipeline.
 *
 * This function advances the command pointer through all commands that are
 * connected by pipe operators (CMD_PIPE), closing any open file descriptors
 * for each skipped command. It stops when it reaches a command that is not
 * part of the pipeline or the end of the command list.
 *
 * @param[in,out] cmd Double pointer to the current command. The function
 *                    modifies the original pointer in the calling context
 *                    to point to the first command after the pipeline.
 */
static void	ft_skip_pipeline(t_cmd **cmd)
{
	*cmd = (*cmd)->next;
	while (*cmd && ft_is_op((*cmd)->prev_op, CMD_PIPE))
	{
		ft_close_cmd_files(*cmd);
		*cmd = (*cmd)->next;
	}
}

/**
 * @brief Skips commands based on logical operator evaluation.
 *
 * This function implements short-circuit evaluation for logical operators
 * (AND/OR). It waits for the previous command to complete (if not a parent
 * builtin), retrieves its exit status, and determines whether to skip
 * subsequent commands based on that status and the logical operators.
 *
 * Commands are skipped when:
 * - Previous command succeeded (lst_stat == 0) and next operator is OR
 * - Previous command failed (lst_stat != 0) and next operator is AND
 *
 * When skipping, entire pipelines are skipped as a unit.
 *
 * @param cmd Pointer to the pointer of the current command. Updated to point
 *            to the next command to execute or NULL if at the end.
 * @param prev_pid Process ID of the previous command (if forked).
 * @param lst_stat Pointer to the last exit status, updated with the exit
 *                 status of the previous command.
 */
static void	ft_skip_based_on_stat(t_cmd **cmd, pid_t prev_pid)
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

void	ft_cleanup_child_exit(t_data *dt, t_cmd *cmd, int status)
{
	ft_close_cmd_files(cmd);
	ft_free_strarr(dt->ms_envp);
	ft_free_prompt_line(dt);
	ft_cleanup_line(dt);
	free(dt->prev_line);
	free(dt);
	exit(status);
}

static void	ft_exec_child(t_data *dt, t_cmd *cmd)
{
	int	status;

	ft_close_unused_fds(cmd->next);
	status = ft_apply_redirs(cmd);
	if (status != EXIT_SUCCESS)
		ft_cleanup_child_exit(dt, cmd, status);
	else if (!cmd->args || !cmd->args[0])
		ft_cleanup_child_exit(dt, cmd, status);
	else if (ft_is_builtin(cmd->args[0]))
		status = ft_exec_builtin(dt, cmd);
	else
		status = ft_exec_cmd(cmd, dt->ms_envp, ft_get_status(0, false));
	ft_cleanup_child_exit(dt, cmd, status);
}

/**
 * @brief Executes a complete command line with all its commands.
 *
 * This is the main execution function that processes an entire command line
 * consisting of potentially multiple commands connected by pipes and logical
 * operators (AND/OR). It iterates through the command linked list, deciding
 * for each command whether to execute it in the parent process (for parent
 * builtins not in pipelines) or fork a child process.
 *
 * The function handles:
 * - Environment variable expansion in command arguments
 * - Parent builtin execution in the parent process
 * - Forking child processes for other commands
 * - Closing file descriptors after use
 * - Short-circuit evaluation of logical operators
 * - Waiting for all child processes to complete
 * - Cleanup of resources
 *
 * After all commands are processed, it waits for any remaining child
 * processes and performs cleanup operations.
 *
 * @param dt Pointer to the main data structure containing the command linked
 *           list, environment variables, process ID array, and last exit
 *           status.
 */
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
			ft_get_status(ft_exec_builtin(dt, cur_cmd), true);
		else
		{
			dt->pid_arr[i] = fork();
			if (dt->pid_arr[i] == 0)
				ft_exec_child(dt, cur_cmd);
			i++;
		}
		ft_close_cmd_files(cur_cmd);
		if (ft_get_status(0, false) == 130)
			break ;
		ft_skip_based_on_stat(&cur_cmd, dt->pid_arr[i]);
	}
	ft_wait_all_pids(dt);
	ft_cleanup_line(dt);
}

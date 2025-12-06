/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:46:07 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/06 19:50:22 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_close_unused_fds(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->infile > STDERR_FILENO)
			close(cmd->infile);
		if (cmd->outfile > STDERR_FILENO)
			close(cmd->outfile);
		cmd = cmd->next;
	}
}

void	ft_close_cmd_files(t_cmd *cmd)
{
	if (cmd->infile > STDERR_FILENO)
		close(cmd->infile);
	if (cmd->outfile > STDERR_FILENO)
		close(cmd->outfile);
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
	ft_get_status(WEXITSTATUS(lst_stat), true);
}

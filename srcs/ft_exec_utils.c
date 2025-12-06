/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:46:07 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/05 22:57:26 by alebarbo         ###   ########.fr       */
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

static t_cmd	*ft_get_last_cmd(t_cmd *cmd_ll)
{
	t_cmd	*cur_cmd;

	if (!cmd_ll)
		return (NULL);
	cur_cmd = cmd_ll;
	while (cur_cmd->next)
		cur_cmd = cur_cmd->next;
	return (cur_cmd);
}

void	ft_wait_all_pids(t_data *dt)
{
	t_cmd	*lst_cmd;
	pid_t	cur_pid;
	int		lst_stat;
	int		i;

	i = 0;
	cur_pid = dt->pid_arr[i];
	while (cur_pid != 0)
	{
		waitpid(cur_pid, &lst_stat, 0);
		cur_pid = dt->pid_arr[i];
		i++;
	}
	lst_cmd = ft_get_last_cmd(dt->cmd_ll);
	if (!ft_is_builtin(lst_cmd->args[0]))
		ft_get_status(lst_stat, true);
}

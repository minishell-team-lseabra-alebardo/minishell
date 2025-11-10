/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:46:07 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/10 15:23:04 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_dup2_close(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return ;
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (oldfd > STDERR_FILENO)
		close(oldfd);
}

void	ft_perror_exit(char *msg, int status)
{
	perror(msg);
	exit(status);
}

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
	int		i;

	i = 0;
	cur_pid = dt->pid_arr[i];
	while (cur_pid != 0)
	{
		waitpid(cur_pid, &dt->lst_stat, 0);
		cur_pid = dt->pid_arr[++i];
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:07:52 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/12 15:14:00 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_free_redirs(t_redir *redir)
{
	if (!redir)
		return ;
	if (redir->next)
		ft_free_redirs(redir->next);
	if (redir->fd_from)
		free(redir->fd_from);
	free(redir);
}

static void	ft_free_cmds(t_cmd *cmd)
{
	size_t	i;

	if (!cmd)
		return ;
	if (cmd->next)
		ft_free_cmds(cmd->next);
	ft_free_redirs(cmd->redir_ll);
	if (cmd->args)
		free(cmd->args);
	if (cmd->dup2_backup)
	{
		i = 0;
		while (cmd->dup2_backup[i])
		{
			free(cmd->dup2_backup[i]);
			i++;
		}
		free(cmd->dup2_backup);
	}
	free(cmd);
}

void	ft_cleanup_line(t_data *dt)
{
	ft_free_cmds(dt->cmd_ll);
	dt->cmd_ll = NULL;
	ft_free_strarr(dt->split_line);
	dt->split_line = NULL;
	ft_bzero(dt->pid_arr, MAX_PROCESSES);
}

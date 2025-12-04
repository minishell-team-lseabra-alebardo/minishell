/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:07:52 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/04 12:32:59 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

/**
 * @brief Frees a linked list of redirection structures.
 *
 * Recursively frees all redirection nodes starting at @p redir, including
 * any dynamically allocated fields such as fd_from.
 *
 * @param redir Pointer to the first redirection node.
 */
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

/**
 * @brief Frees a linked list of command structures.
 *
 * Recursively frees all commands, including their redirection lists, argument
 * arrays, and any stored backup entries used for dup2 restoration.
 *
 * @param cmd Pointer to the first command node.
 */
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

/**
 * @brief Cleans all data associated with the currently parsed command line.
 *
 * Frees the command list stored in dt->cmd_ll, releases the split_line array,
 * and resets the pid array used during execution.
 *
 * @param dt Pointer to the shell data structure.
 */
void	ft_cleanup_line(t_data *dt)
{
	ft_free_cmds(dt->cmd_ll);
	dt->cmd_ll = NULL;
	ft_free_strarr(dt->split_line);
	dt->split_line = NULL;
	ft_bzero(dt->pid_arr, MAX_PROCESSES);
}

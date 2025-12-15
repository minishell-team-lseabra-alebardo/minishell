/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:26:42 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/15 15:40:35 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_dup2_close(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return ;
	if (dup2(oldfd, newfd) == -1)
		ft_puterror("dup2", NULL, NULL);
	else if (oldfd > STDERR_FILENO)
		close(oldfd);
}

static void	ft_add_to_backup(int savefd, int newfd, t_cmd *cmd)
{
	int		**new_dup2_backup;
	size_t	i;

	i = 0;
	while (cmd->dup2_backup && cmd->dup2_backup[i])
		i++;
	new_dup2_backup = ft_calloc((i + 2), sizeof(int *));
	if (!new_dup2_backup)
		return ;
	if (cmd->dup2_backup)
	{
		ft_memcpy(new_dup2_backup, cmd->dup2_backup, i * sizeof(int *));
		free(cmd->dup2_backup);
	}
	cmd->dup2_backup = new_dup2_backup;
	cmd->dup2_backup[i] = ft_calloc(2, sizeof(int));
	if (!cmd->dup2_backup[i])
	{
		close(savefd);
		return ;
	}
	cmd->dup2_backup[i][0] = savefd;
	cmd->dup2_backup[i][1] = newfd;
}

void	ft_dup2_backup_close(int oldfd, int newfd, t_cmd *cmd)
{
	int	savefd;

	if (oldfd == newfd)
		return ;
	savefd = dup(newfd);
	ft_dup2_close(oldfd, newfd);
	ft_add_to_backup(savefd, newfd, cmd);
}

void	ft_reset_dup2(t_cmd *cmd)
{
	size_t	i;
	int		*cur_backup;

	if (!cmd || !cmd->dup2_backup)
		return ;
	i = 0;
	while (cmd->dup2_backup[i])
	{
		cur_backup = cmd->dup2_backup[i];
		ft_dup2_close(cur_backup[0], cur_backup[1]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:26:42 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/04 12:38:07 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

/**
 * @brief Performs a dup2() redirection and closes the old FD when appropriate.
 *
 * If oldfd and newfd differ, dup2(oldfd, newfd) is attempted. On success,
 * oldfd is closed if it is not a standard descriptor (STDERR_FILENO or below).
 * Errors are reported via ft_puterror().
 *
 * @param oldfd The source file descriptor.
 * @param newfd The destination file descriptor.
 */
void	ft_dup2_close(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return ;
	if (dup2(oldfd, newfd) == -1)
		ft_puterror("dup2", NULL, NULL);
	else if (oldfd > STDERR_FILENO)
		close(oldfd);
}

/**
 * @brief Adds a dup2 backup entry to a command's backup list.
 *
 * Stores a pointer representing a saved FD pair in cmd->dup2_backup,
 * expanding the array as needed. Used to track redirections that must be
 * restored later.
 *
 * @param backup Pointer to a two-int array {saved_fd, target_fd}.
 * @param cmd    Pointer to the command whose backup list is updated.
 * @return SUCCESS on success, ERROR on allocation failure.
 */
static int	ft_add_to_backup(int *backup, t_cmd *cmd)
{
	int		**new_dup2_backup;
	size_t	i;

	i = 0;
	while (cmd->dup2_backup && cmd->dup2_backup[i])
		i++;
	new_dup2_backup = ft_calloc((i + 2), sizeof(int *));
	if (!new_dup2_backup)
		return (ERROR);
	if (!cmd->dup2_backup)
		*new_dup2_backup = backup;
	else
	{
		ft_memcpy(new_dup2_backup, cmd->dup2_backup, i * sizeof(int *));
		new_dup2_backup[i] = backup;
		free(cmd->dup2_backup);
	}
	cmd->dup2_backup = new_dup2_backup;
	return (SUCCESS);
}

/**
 * @brief Performs a dup2 redirection while saving the original FD for later
 *restore them if the command is executed in the parent proccess.
 *
 * Saves the current value of newfd, performs the redirection using
 * ft_dup2_close(), and records the backup pair in cmd->dup2_backup.
 * If backup storage fails, the saved FD is discarded.
 *
 * @param oldfd The source FD for dup2().
 * @param newfd The destination FD to overwrite.
 * @param cmd   Pointer to the command owning the backup list.
 */
void	ft_dup2_backup_close(int oldfd, int newfd, t_cmd *cmd)
{
	int	savefd;
	int	*backup;

	if (oldfd == newfd)
		return ;
	backup = ft_calloc(2, sizeof(int));
	if (!backup)
		return ;
	savefd = dup(newfd);
	ft_dup2_close(oldfd, newfd);
	backup[0] = savefd;
	backup[1] = newfd;
	if (ft_add_to_backup(backup, cmd) == ERROR)
	{
		close(savefd);
		free(backup);
	}
}

/**
 * @brief Restores all file descriptors saved in a command's dup2 backup list.
 *
 * Iterates over cmd->dup2_backup, restoring each saved state using
 * ft_dup2_close(). This is typically used after redirections applied
 * in the parent process.
 *
 * @param cmd Pointer to the command whose saved FDs should be restored.
 */
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

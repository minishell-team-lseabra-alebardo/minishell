/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:01:44 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/14 18:55:48 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_handle_path_failure(t_cmd *cmd, int status)
{
	char	*message;
	char	*target;

	if (cmd && cmd->args && cmd->args[0] && !cmd->args[0][0])
		target = "\"\"";
	else if (cmd && cmd->args)
		target = cmd->args[0];
	else
		target = NULL;
	if (status == EXIT_NOT_FOUND)
		message = ERR_CMD_NOT_FOUND;
	else if (status == EXIT_CANNOT_EXEC && ft_is_directory(cmd->args[0]))
		message = ERR_IS_DIR;
	else if (status == EXIT_CANNOT_EXEC)
		message = ERR_NO_PERMISSION;
	else
		message = ERR_GENERIC;
	ft_puterror(NULL, target, message);
	ft_get_status(status, true);
}

static int	ft_exec_cmd(t_cmd *cmd, char **ms_envp)
{
	char	*path;

	path = NULL;
	ft_dup2_close(cmd->infile, STDIN_FILENO);
	ft_dup2_close(cmd->outfile, STDOUT_FILENO);
	ft_get_status(ft_resolve_cmd_path(cmd->args[0], &path), true);
	if (ft_get_status(0, false) != EXIT_SUCCESS)
	{
		ft_handle_path_failure(cmd, ft_get_status(0, false));
		return (ft_get_status(0, false));
	}
	execve(path, cmd->args, ms_envp);
	perror("execve");
	free(path);
	return (EXIT_FAILURE);
}

static void	ft_cleanup_child_exit(t_data *dt, t_cmd *cmd, int status)
{
	ft_close_cmd_files(cmd);
	ft_free_strarr(dt->ms_envp);
	ft_free_prompt_line(dt);
	ft_cleanup_line(dt);
	free(dt);
	exit(status);
}

void	ft_exec_child(t_data *dt, t_cmd *cmd)
{
	int	status;

	ft_close_unused_fds(cmd->next);
	status = ft_apply_redirs(cmd);
	if (status != EXIT_SUCCESS || ft_get_status(0, false) == 130)
		ft_cleanup_child_exit(dt, cmd, status);
	else if (!cmd->args || !cmd->args[0])
		ft_cleanup_child_exit(dt, cmd, status);
	else if (ft_is_builtin(cmd->args[0]))
		status = ft_exec_builtin(dt, cmd);
	else
		status = ft_exec_cmd(cmd, dt->ms_envp);
	ft_cleanup_child_exit(dt, cmd, status);
}

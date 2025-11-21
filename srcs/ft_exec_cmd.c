/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:01:44 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/21 18:20:11 by alebarbo         ###   ########.fr       */
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

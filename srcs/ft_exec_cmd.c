/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:01:44 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/07 17:32:07 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

/**
 * @brief Handles path resolution failures for command execution.
 *
 * This function determines the appropriate error message based on the
 * failure status code and prints it before exiting. It handles three
 * types of failures: command not found (EXIT_NOT_FOUND), permission
 * denied (EXIT_CANNOT_EXEC), and generic errors.
 *
 * The function does not return as it terminates the process with the
 * given status code.
 *
 * @param cmd Pointer to the command structure containing the command name.
 * @param status The error status code indicating the type of failure.
 */
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
	else if (status == EXIT_CANNOT_EXEC)
		message = ERR_NO_PERMISSION;
	else
		message = ERR_GENERIC;
	ft_puterror_exit(NULL, target, message, status);
}

/**
 * @brief Executes an external command in a child process.
 *
 * This function sets up the execution environment for an external command
 * by redirecting file descriptors for stdin/stdout, preparing the subshell
 * environment, and resolving the command's executable path. If the command
 * is a subshell expression, it is prepared accordingly. Otherwise, the
 * function searches for the command in the PATH environment variable.
 *
 * If path resolution succeeds, execve() is called to replace the current
 * process with the target command. If execve() fails, resources are cleaned
 * up and an error is reported. If path resolution fails, the function
 * handles the error appropriately and exits with the corresponding status.
 *
 * This function should only be called in a child process as it uses execve()
 * which replaces the current process image.
 *
 * @param cmd Pointer to the command structure containing arguments and file
 *            descriptors for redirections.
 * @param ms_envp Array of environment variable strings to pass to the
 *                executed command.
 * @param lst_stat The last exit status from the previous command, used for
 *                 subshell preparation.
 */
void	ft_exec_cmd(t_cmd *cmd, char **ms_envp, int lst_stat)
{
	char	*path;

	path = NULL;
	ft_dup2_close(cmd->infile, STDIN_FILENO);
	ft_dup2_close(cmd->outfile, STDOUT_FILENO);
	if (ft_prep_subshell(ms_envp, cmd, &path, lst_stat))
		ft_get_status(EXIT_SUCCESS, true);
	else
		ft_get_status(ft_resolve_cmd_path(cmd->args[0], &path), true);
	if (ft_get_status(0, false) != EXIT_SUCCESS)
		ft_handle_path_failure(cmd, ft_get_status(0, false));
	execve(path, cmd->args, ms_envp);
	free(path);
	ft_close_cmd_files(cmd);
	perror("execve");
}

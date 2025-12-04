/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:01:44 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/04 12:57:48 by lseabra-         ###   ########.fr       */
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
	char	*msg;

	if (status == EXIT_NOT_FOUND)
		msg = ERR_CMD_NOT_FOUND;
	else if (status == EXIT_CANNOT_EXEC)
		msg = ERR_NO_PERMISSION;
	else
		msg = ERR_GENERIC;
	ft_puterror_exit(NULL, cmd->args[0], msg, status);
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
	int		status;

	path = NULL;
	ft_dup2_close(cmd->infile, STDIN_FILENO);
	ft_dup2_close(cmd->outfile, STDOUT_FILENO);
	if (ft_prep_subshell(ms_envp, cmd, &path, lst_stat))
		status = EXIT_SUCCESS;
	else
		status = ft_resolve_cmd_path(cmd->args[0], &path);
	if (status != EXIT_SUCCESS)
		ft_handle_path_failure(cmd, status);
	execve(path, cmd->args, ms_envp);
	free(path);
	ft_close_cmd_files(cmd);
	perror("execve");
}

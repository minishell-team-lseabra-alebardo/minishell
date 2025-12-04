/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:44:08 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/04 12:53:17 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

/**
 * @brief Checks if a command is part of a pipeline.
 *
 * This function determines whether the given command is connected to other
 * commands via pipe operators. A command is considered to be in a pipeline
 * if either its previous operator is a pipe (CMD_PIPE) or if it has a next
 * command whose previous operator is a pipe.
 *
 * @param cmd Pointer to the command structure to check.
 * @return true if the command is part of a pipeline, false otherwise.
 */
bool	ft_is_in_pipeline(t_cmd *cmd)
{
	if (!cmd)
		return (false);
	else if (ft_is_op(cmd->prev_op, CMD_PIPE))
		return (true);
	else if (cmd->next && ft_is_op(cmd->next->prev_op, CMD_PIPE))
		return (true);
	else
		return (false);
}

/**
 * @brief Checks if a command is a parent-context builtin.
 *
 * Parent-context builtins are commands that must be executed in the parent
 * shell process because they modify the shell's environment or state. These
 * include: cd (changes directory), exit (terminates shell), export (sets
 * environment variables), and unset (removes environment variables).
 *
 * @param cmd String containing the command name to check.
 * @return true if the command is a parent-context builtin, false otherwise.
 */
bool	ft_is_parent_bltn(char *cmd)
{
	if (!cmd)
		return (false);
	else if (ft_strncmp("cd", cmd, 3) == 0)
		return (true);
	else if (!ft_strncmp("exit", cmd, 5))
		return (true);
	else if (ft_strncmp("export", cmd, 7) == 0)
		return (true);
	else if (ft_strncmp("unset", cmd, 6) == 0)
		return (true);
	else
		return (false);
}

/**
 * @brief Checks if a command is a builtin command.
 *
 * This function determines whether the given command name corresponds to
 * any of the shell's builtin commands, including both parent-context builtins
 * (cd, exit, export, unset) and child-compatible builtins (pwd, echo, env).
 *
 * @param cmd String containing the command name to check.
 * @return true if the command is a builtin, false otherwise.
 */
bool	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	else if (ft_is_parent_bltn(cmd))
		return (true);
	else if (ft_strncmp("pwd", cmd, 4) == 0)
		return (true);
	else if (ft_strncmp("echo", cmd, 5) == 0)
		return (true);
	else if (ft_strncmp("env", cmd, 4) == 0)
		return (true);
	else
		return (false);
}

/**
 * @brief Executes a builtin command.
 *
 * This function handles the execution of all builtin shell commands. It
 * first applies any input/output redirections specified for the command.
 * If redirections succeed, it duplicates the appropriate file descriptors
 * for stdin/stdout, then dispatches to the specific builtin handler based
 * on the command name.
 *
 * After execution, file descriptors are restored to their original state.
 * If the command is part of a pipeline, the function terminates the child
 * process with lst_stat after execution.
 *
 * Supported builtins: cd, exit, pwd, export, echo, unset, env.
 *
 * @param dt Pointer to the main data structure containing shell state and
 *           environment.
 * @param cmd Pointer to the command structure containing arguments and
 *            redirections.
 * @return The exit status of the builtin command (EXIT_SUCCESS or
 *         EXIT_FAILURE).
 */
int	ft_exec_builtin(t_data *dt, t_cmd *cmd)
{
	int	lst_stat;

	lst_stat = ft_apply_redirs(cmd);
	if (lst_stat != EXIT_SUCCESS)
		return (lst_stat);
	ft_dup2_backup_close(cmd->infile, STDIN_FILENO, cmd);
	ft_dup2_backup_close(cmd->outfile, STDOUT_FILENO, cmd);
	if (ft_strncmp("cd", cmd->args[0], 3) == 0)
		lst_stat = ft_change_directory(dt, cmd);
	else if (ft_strncmp("exit", cmd->args[0], 5) == 0)
		ft_exit(dt, cmd);
	else if (ft_strncmp("pwd", cmd->args[0], 4) == 0)
		lst_stat = ft_pwd();
	else if (ft_strncmp("export", cmd->args[0], 7) == 0)
		lst_stat = ft_export(cmd, dt);
	else if (ft_strncmp("echo", cmd->args[0], 5) == 0)
		ft_echo(cmd->args);
	else if (ft_strncmp("unset", cmd->args[0], 6) == 0)
		ft_unset(dt, cmd->args);
	else if (ft_strncmp("env", cmd->args[0], 4) == 0)
		ft_env(dt->ms_envp);
	ft_reset_dup2(cmd);
	if (ft_is_in_pipeline(cmd))
		exit(lst_stat);
	return (lst_stat);
}

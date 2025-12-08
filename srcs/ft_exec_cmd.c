/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:01:44 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/08 18:43:00 by alebarbo         ###   ########.fr       */
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
	else if (status == EXIT_CANNOT_EXEC)
		message = ERR_NO_PERMISSION;
	else
		message = ERR_GENERIC;
	ft_puterror(NULL, target, message);
	ft_get_status(status, true);
}

int	ft_exec_cmd(t_cmd *cmd, char **ms_envp, int lst_stat)
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
	{
		ft_handle_path_failure(cmd, ft_get_status(0, false));
		return (ft_get_status(0, false));
	}
	execve(path, cmd->args, ms_envp);
	perror("execve");
	free(path);
	return (EXIT_FAILURE);
}

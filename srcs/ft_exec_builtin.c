/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:44:08 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/02 15:52:48 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

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

bool	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strncmp("cd", cmd, 3) == 0)
		return (true);
	else if (!ft_strncmp("exit", cmd, 5))
		return (true);
	else if (ft_strncmp("pwd", cmd, 4) == 0)
		return (true);
	// if (ft_strncmp("echo", cmd, 5) == 0)
	// 	return (true);
	// else if (ft_strncmp("export", cmd, 7) == 0)
	// 	return (true);
	// else if (ft_strncmp("unset", cmd, 6) == 0)
	// 	return (true);
	else if (ft_strncmp("env", cmd, 4) == 0)
	 	return (true);
	else
		return (false);
}

void	ft_exec_builtin(t_data *dt, t_cmd *cmd)
{
	if (ft_strncmp("cd", cmd->args[0], 3) == 0)
		dt->lst_stat = ft_change_directory(dt, cmd);
	else if (ft_strncmp("exit", cmd->args[0], 5) == 0)
		ft_exit(dt, cmd);
	else if (ft_strncmp("pwd", cmd->args[0], 4) == 0)
		dt->lst_stat = ft_pwd();
	// if (ft_strncmp("echo", cmd->args[0], 5) == 0)
	// 	TODO()
	// else if (ft_strncmp("export", cmd->args[0], 7) == 0)
	// 	TODO()
	// else if (ft_strncmp("unset", cmd->args[0], 6) == 0)
	// 	TODO()
	else if (ft_strncmp("env", cmd->args[0], 4) == 0)
		ft_env(dt->ms_envp);
	if (ft_is_in_pipeline(cmd))
		exit(EXIT_SUCCESS);
}

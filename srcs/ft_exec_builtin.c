/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:44:08 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/21 12:59:16 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

bool	ft_is_builtin(char *cmd)
{
	if (ft_strncmp("cd", cmd, 3))
		return (true);
	// if (ft_strncmp("echo", cmd, 5))
	// 	return (true);
	// else if (ft_strncmp("pwd", cmd, 4))
	// 	return (true);
	// else if (ft_strncmp("export", cmd, 7))
	// 	return (true);
	// else if (ft_strncmp("unset", cmd, 6))
	// 	return (true);
	// else if (ft_strncmp("env", cmd, 6))
	// 	return (true);
	else
		return (false);
}

void	ft_exec_builtin(t_data *dt, t_cmd *cmd)
{
	if (ft_strncmp("cd", cmd->args[0], 3))
		ft_change_directory(dt, cmd);
	// if (ft_strncmp("echo", cmd, 5))
	// 	TODO()
	// else if (ft_strncmp("pwd", cmd, 4))
	// 	TODO()
	// else if (ft_strncmp("export", cmd, 7))
	// 	TODO()
	// else if (ft_strncmp("unset", cmd, 6))
	// 	TODO()
	// else if (ft_strncmp("env", cmd, 6))
	// 	TODO()
}

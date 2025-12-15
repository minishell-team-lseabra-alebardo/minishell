/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:44:08 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/15 17:48:49 by lseabra-         ###   ########.fr       */
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

bool	ft_is_pbtin(char *cmd)
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

bool	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	else if (ft_is_pbtin(cmd))
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

static int	ft_setup_builtin_redirs(t_cmd *cmd, int	*lst_stat)
{
	if (ft_is_pbtin(cmd->args[0]))
	{
		*lst_stat = ft_apply_redirs(cmd);
		if (*lst_stat != EXIT_SUCCESS)
			return (ERROR);
		ft_dup2_backup_close(cmd->infile, STDIN_FILENO, cmd);
		ft_dup2_backup_close(cmd->outfile, STDOUT_FILENO, cmd);
	}
	else
	{
		ft_dup2_close(cmd->infile, STDIN_FILENO);
		ft_dup2_close(cmd->outfile, STDOUT_FILENO);
	}
	return (SUCCESS);
}

int	ft_exec_builtin(t_data *dt, t_cmd *cmd)
{
	int	lst_stat;

	lst_stat = EXIT_SUCCESS;
	if (ft_setup_builtin_redirs(cmd, &lst_stat) == ERROR)
		return (lst_stat);
	if (ft_strncmp("cd", cmd->args[0], 3) == 0)
		lst_stat = ft_change_directory(dt, cmd);
	else if (ft_strncmp("exit", cmd->args[0], 5) == 0)
		ft_exit(dt, cmd);
	else if (ft_strncmp("pwd", cmd->args[0], 4) == 0)
		lst_stat = ft_pwd();
	else if (ft_strncmp("export", cmd->args[0], 7) == 0)
		lst_stat = ft_export(cmd, dt);
	else if (ft_strncmp("echo", cmd->args[0], 5) == 0)
		lst_stat = ft_echo(cmd->args);
	else if (ft_strncmp("unset", cmd->args[0], 6) == 0)
		lst_stat = ft_unset(dt, cmd->args);
	else if (ft_strncmp("env", cmd->args[0], 4) == 0)
		lst_stat = ft_env(dt->ms_envp);
	ft_reset_dup2(cmd);
	return (lst_stat);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_directory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:53:43 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/12 15:14:24 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	ft_change_directory(t_data *dt, t_cmd *cmd)
{
	char	*pwd;
	char	*path;

	ft_close_cmd_files(cmd);
	if (!cmd->args[1])
		path = ft_getenv("HOME", dt->ms_envp);
	else if (cmd->args[2])
		return (ft_puterror_ret("cd", NULL, ERR_TOO_MANY_ARGS, EXIT_FAILURE));
	else if (cmd->args[1][0] == '\0')
		return (EXIT_SUCCESS);
	else
		path = cmd->args[1];
	pwd = getcwd(0, 0);
	if (chdir(path) < 0)
	{
		free(pwd);
		ft_puterror("cd", cmd->args[1], NULL);
		return (EXIT_FAILURE);
	}
	ft_set_env("OLDPWD", pwd, dt->ms_envp);
	free(pwd);
	pwd = getcwd(0, 0);
	ft_set_env("PWD", pwd, dt->ms_envp);
	free(pwd);
	return (EXIT_SUCCESS);
}

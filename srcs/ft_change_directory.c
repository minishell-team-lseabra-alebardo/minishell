/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_directory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:53:43 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/14 15:49:38 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_set_pwds(t_data *dt, char *pwd)
{
	ft_set_env(dt, "OLDPWD", pwd);
	free(pwd);
	pwd = getcwd(NULL, 0);
	ft_set_env(dt, "PWD", pwd);
	free(pwd);
}

int	ft_change_directory(t_data *dt, t_cmd *cmd)
{
	char	*pwd;
	char	*path;

	ft_close_cmd_files(cmd);
	if (!cmd->args[1])
	{
		path = ft_getenv("HOME", dt->ms_envp);
		if (!path)
			return (ft_puterror_ret("cd", NULL, ERR_HOME_NT_SET, EXIT_FAILURE));
	}
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
	ft_set_pwds(dt, pwd);
	return (EXIT_SUCCESS);
}

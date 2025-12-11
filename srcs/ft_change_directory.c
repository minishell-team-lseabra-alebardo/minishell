/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_directory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:53:43 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/11 15:37:08 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

/**
 * @brief Changes the current working directory for the minishell session.
 *
 * Implements the behavior of the `cd` builtin. If no argument is provided,
 * the function attempts to change to the directory stored in the HOME
 * environment variable. If more than one argument is given, an error is
 * returned. Empty arguments (e.g., `cd ""`) are ignored successfully.
 *
 * On success, the function updates the PWD and OLD_PWD environment variables.
 *
 * @param dt  Pointer to the minishell main data structure.
 * @param cmd Pointer to the parsed command structure containing arguments.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
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

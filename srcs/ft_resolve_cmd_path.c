/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolve_cmd_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:45:27 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/18 17:08:43 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static bool	ft_is_directory(char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK) == ERROR)
		return (false);
	if (stat(path, &path_stat) == ERROR)
		return (ft_puterror_ret("stat", NULL, NULL, false));
	if (S_ISDIR(path_stat.st_mode) == 1)
		return (true);
	else
		return (false);
}

static int	ft_check_abs_path(char *cmd, char **path_addr)
{
	if (ft_is_directory(cmd))
	{
		ft_puterror(NULL, cmd, ERR_IS_DIR);
		return (EXIT_CANNOT_EXEC);
	}
	if (access(cmd, F_OK | X_OK) == 0)
	{
		*path_addr = ft_strdup(cmd);
		return (EXIT_SUCCESS);
	}
	else if (access(cmd, F_OK) == 0)
	{
		ft_puterror(NULL, cmd, ERR_NO_PERMISSION);
		return (EXIT_CANNOT_EXEC);
	}
	else
	{
		ft_puterror(NULL, cmd, ERR_NO_FILE_DIR);
		return (EXIT_NOT_FOUND);
	}
}

static char	*ft_build_check_path(char *cmd, char *cur_path, int *status)
{
	char	*complete_path;

	complete_path = ft_strjoin(cur_path, "/");
	complete_path = ft_strjoin_free(complete_path, true, cmd, false);
	if (access(complete_path, F_OK | X_OK) == 0)
	{
		*status = EXIT_SUCCESS;
		return (complete_path);
	}
	else if (access(complete_path, F_OK) == 0 && *status == EXIT_NOT_FOUND)
		*status = EXIT_CANNOT_EXEC;
	free(complete_path);
	return (NULL);
}

static int	ft_search_in_path(char *cmd, char **path_addr, char **path_arr)
{
	int		i;
	int		status;

	status = EXIT_NOT_FOUND;
	if (!cmd || !cmd[0])
		return (status);
	i = 0;
	while (path_arr[i])
	{
		*path_addr = ft_build_check_path(cmd, path_arr[i], &status);
		if (*path_addr)
			return (status);
		i++;
	}
	if (status == EXIT_NOT_FOUND)
		ft_puterror(NULL, cmd, ERR_CMD_NOT_FOUND);
	else if (status == EXIT_CANNOT_EXEC)
		ft_puterror(NULL, cmd, ERR_NO_PERMISSION);
	return (status);
}

int	ft_resolve_cmd_path(char *cmd, char **ms_envp, char **path_addr)
{
	char	**path_arr;
	int		status;
	char	*path;

	path = ft_getenv("PATH", ms_envp);
	if (ft_strchr(cmd, '/') || !path)
		return (ft_check_abs_path(cmd, path_addr));
	path_arr = ft_split(path, ':');
	status = ft_search_in_path(cmd, path_addr, path_arr);
	ft_free_strarr(path_arr);
	return (status);
}

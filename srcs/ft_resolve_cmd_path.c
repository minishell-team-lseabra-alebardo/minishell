/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolve_cmd_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:45:27 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/06 16:52:58 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static int	ft_check_abs_path(char *cmd, char **path_addr)
{
	if (access(cmd, F_OK | X_OK) == 0)
	{
		*path_addr = ft_strdup(cmd);
		return (EXIT_SUCCESS);
	}
	else if (access(cmd, F_OK) == 0)
		return (EXIT_CANNOT_EXEC);
	else
		return (EXIT_NOT_FOUND);
}

static int	ft_search_in_path(char *cmd, char **path_addr, char **path_arr)
{
	int		i;
	int		status;
	char	*dir_path;
	char	*complete_path;

	status = EXIT_NOT_FOUND;
	if (!cmd || !cmd[0])
		return (status);
	i = 0;
	while (path_arr[i])
	{
		dir_path = ft_strjoin(path_arr[i], "/");
		complete_path = ft_strjoin(dir_path, cmd);
		free(dir_path);
		if (access(complete_path, F_OK | X_OK) == 0)
		{
			*path_addr = complete_path;
			return (EXIT_SUCCESS);
		}
		else if (access(complete_path, F_OK) == 0 && status == EXIT_NOT_FOUND)
			status = EXIT_CANNOT_EXEC;
		free(complete_path);
		i++;
	}
	return (status);
}

int	ft_resolve_cmd_path(char *cmd, char **path_addr)
{
	char	**path_arr;
	char	*path;
	int		status;

	if (ft_strchr(cmd, '/'))
		return (ft_check_abs_path(cmd, &path));
	path_arr = ft_split(getenv("PATH"), ':');
	status = ft_search_in_path(cmd, path_addr, path_arr);
	ft_free_strarr(path_arr);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:15:30 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/07 16:04:35 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static char	*ft_get_pwd(char **ms_envp)
{
	int		i;

	i = 0;
	while (ft_strncmp(ms_envp[i], "PWD=", 4))
		i++;
	return (ms_envp[i] + 4);
}

static int	ft_get_path(char **ms_envp)
{
	int		i;

	i = 0;
	while (ft_strncmp(ms_envp[i], "PATH=", 5))
		i++;
	return (i);
}

static char	*ft_expand_path(char *pwd, char *path)
{
	char	*new_path;
	int		i;
	int		j;

	new_path = (char *) ft_calloc(ft_strlen(pwd) + ft_strlen(path) + 2, 1);
	if (!new_path)
		return (0);
	i = 0;
	while (path[i])
	{
		new_path[i] = path[i];
		i++;
	}
	new_path[i] = ':';
	i++;
	j = 0;
	while (pwd[j])
	{
		new_path[i] = pwd[j];
		i++;
		j++;
	}
	free(path);
	return (new_path);
}

void	ft_ms_path(char **ms_envp)
{
	char	*pwd;
	int		path;

	pwd = ft_get_pwd(ms_envp);
	path = ft_get_path(ms_envp);
	ms_envp[path] = ft_expand_path(pwd, ms_envp[path]);
}

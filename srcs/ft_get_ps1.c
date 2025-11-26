/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_ps1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:03:27 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/26 15:05:47 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	*ft_get_hostname(void)
{
	char	*ref;
	char	*hostname;
	char	*res;
	size_t	size;

	ref = "local/";
	hostname = getenv("SESSION_MANAGER");
	if (!hostname)
		return (NULL);
	if (ft_strncmp(hostname, ref, ft_strlen(ref)) == 0)
		hostname += ft_strlen(ref);
	if (*hostname == 0)
		return (NULL);
	size = 0;
	while (hostname[size] && hostname[size] != '.' && hostname[size] != ':')
		size++;
	res = ft_substr(hostname, 0, size);
	return (res);
}

static char	*ft_strjoin_free(char *malloc_str, char *str)
{
	char	*res;

	res = ft_strjoin(malloc_str, str);
	free(malloc_str);
	return (res);
}

static char	*ft_get_prompt_cwd(char **ms_envp)
{
	char	*cwd;
	char	*home;

	cwd = ft_getenv("PWD", ms_envp);
	home = ft_getenv("HOME", ms_envp);
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		cwd += ft_strlen(home);
		cwd = ft_strjoin("~", cwd);
	}
	else if (cwd)
		cwd = ft_strdup(cwd);
	return (cwd);
}

char	*ft_get_ps1(char **ms_envp)
{
	char	*username;
	char	*hostname;
	char	*cwd;
	char	*res;

	username = getenv("USER");
	hostname = ft_get_hostname();
	cwd = ft_get_prompt_cwd(ms_envp);
	res = ft_strdup("");
	if (username)
		res = ft_strjoin_free(res, username);
	if (hostname)
	{
		res = ft_strjoin_free(res, "@");
		res = ft_strjoin_free(res, hostname);
		free(hostname);
		res = ft_strjoin_free(res, ":");
	}
	res = ft_strjoin_free(res, cwd);
	free(cwd);
	res = ft_strjoin_free(res, "$ ");
	return (res);
}

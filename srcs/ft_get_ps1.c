/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_ps1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:03:27 by lseabra-          #+#    #+#             */
/*   Updated: 2025/10/01 12:11:01 by lseabra-         ###   ########.fr       */
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
	while (ft_strncmp(hostname, ref, ft_strlen(ref)) != 0)
		hostname++;
	if (*hostname == 0)
		return (NULL);
	hostname += ft_strlen(ref);
	size = 0;
	while (hostname[size] && hostname[size] != '.' && hostname[size] != ':')
		size++;
	res = ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, hostname, size + 1);
	return (res);
}

static char	*ft_join_free(char *malloc_str, char *str)
{
	char	*res;

	res = ft_strjoin(malloc_str, str);
	free(malloc_str);
	return (res);
}

char	*ft_get_ps1(void)
{
	char	*username;
	char	*hostname;
	char	*cwd;
	char	*res;

	username = getenv("USER");
	hostname = ft_get_hostname();
	cwd = getcwd(0, 0);
	res = "\0";
	if (username)
		res = ft_strjoin(res, username);
	if (hostname)
	{
		res = ft_join_free(res, "@");
		res = ft_join_free(res, hostname);
		free(hostname);
		res = ft_join_free(res, " ");
	}
	res = ft_join_free(res, cwd);
	free(cwd);
	res = ft_join_free(res, "$ ");
	return (res);
}

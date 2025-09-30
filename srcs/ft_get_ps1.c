/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_ps1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:03:27 by lseabra-          #+#    #+#             */
/*   Updated: 2025/09/30 16:30:48 by lseabra-         ###   ########.fr       */
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

// char	*ft_joinfree(char *s1, char *s2)
// {
// 	char	*res;
// 	char	*temp;

// 	temp = res;
// 	res = ft_strjoin(res, "@");
// 	free(temp);
// }
char	*ft_get_ps1(void)
{
	char	*username;
	char	*hostname;
	char	*cwd;
	char	*temp;
	char	*res;

	username = getenv("USER");
	hostname = ft_get_hostname();
	cwd = getcwd(0, 0);
	res = "\0";
	if (username)
		res = ft_strjoin(res, username);
	if (hostname)
	{
		temp = res;
		res = ft_strjoin(res, "@");
		free(temp);
		temp = res;
		res = ft_strjoin(res, hostname);
		free(temp);
		temp = res;
		res = ft_strjoin(res, " ");
		free(temp);
	}
	temp = res;
	res = ft_strjoin(res, cwd);
	free(temp);
	free(cwd);
	temp = res;
	res = ft_strjoin(res, "$ ");
	free(temp);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_ps1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:03:27 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/03 13:48:17 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	*ft_strjoin_free(char *s1, bool free_s1, char *s2, bool free_s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (res);
}

static char	*ft_get_prompt_cwd(char **ms_envp)
{
	char	*cwd;
	char	*home;
	char	*tmp;

	cwd = ft_getenv("PWD", ms_envp);
	home = ft_getenv("HOME", ms_envp);
	if (home && ft_strlen(home) < 2)
		home = NULL;
	if (cwd)
		cwd = ft_strdup(cwd);
	else
		cwd = getcwd(0, 0);
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		tmp = cwd;
		cwd = ft_strjoin("~", cwd + ft_strlen(home));
		free(tmp);
	}
	return (cwd);
}

char	*ft_get_ps1(char **ms_envp)
{
	char	*cwd;
	char	*res;

	cwd = ft_get_prompt_cwd(ms_envp);
	res = ft_strjoin(ORANGE, "[");
	res = ft_strjoin_free(res, true, PGM_NAME, false);
	res = ft_strjoin_free(res, true, "]", false);
	res = ft_strjoin_free(res, true, WHITE, false);
	res = ft_strjoin_free(res, true, ":", false);
	res = ft_strjoin_free(res, true, BLUE_GULF, false);
	res = ft_strjoin_free(res, true, cwd, true);
	res = ft_strjoin_free(res, true, RESET, false);
	res = ft_strjoin_free(res, true, "$ ", false);
	return (res);
}

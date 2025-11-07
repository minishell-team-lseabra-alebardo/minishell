/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:15:30 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/07 14:54:17 by alebarbo         ###   ########.fr       */
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

char	*ft_ms_path(char **ms_envp)
{
	char	*pwd;
	char	*ms_path;

	pwd = ft_get_pwd(ms_envp);
	ms_path	= (char *) ft_calloc(ft_strlen(pwd) + 12, sizeof(char));
	ft_strlcpy(ms_path, pwd, ft_strlen(pwd) + 1);
	ft_strlcat(ms_path, "/minishell", ft_strlen(pwd) + 11);
	return (ms_path);
}

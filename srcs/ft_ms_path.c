/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:15:30 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/04 11:41:17 by lseabra-         ###   ########.fr       */
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

char	**ft_expand_envp(char **ms_envp)
{
	char	**expanded_envp;
	int		i;

	i = 0;
	while (ms_envp[i])
		i++;
	expanded_envp = (char **) ft_calloc(i + 2, sizeof(char *));
	if (!expanded_envp)
		return (0);
	i = 0;
	while (ms_envp[i])
	{
		expanded_envp[i] = ms_envp[i];
		i++;
	}
	free(ms_envp);
	return (expanded_envp);
}

int	ft_ms_path(t_data *dt)
{
	char	*pwd;
	int		i;

	i = 0;
	dt->ms_envp = ft_expand_envp(dt->ms_envp);
	if (!dt->ms_envp)
		return (ERROR);
	pwd = ft_get_pwd(dt->ms_envp);
	while (dt->ms_envp[i])
		i++;
	dt->ms_envp[i] = (char *) ft_calloc(ft_strlen(pwd) + 19, 1);
	if (!dt->ms_envp[i])
		return (ERROR);
	ft_strlcpy(dt->ms_envp[i], "MS_PATH=", 9);
	ft_strlcat(dt->ms_envp[i], pwd, ft_strlen(pwd) + 19);
	ft_strlcat(dt->ms_envp[i], "/minishell", ft_strlen(pwd) + 19);
	return (0);
}

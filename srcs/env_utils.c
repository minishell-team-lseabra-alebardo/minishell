/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:23:25 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/26 14:58:52 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

char	**ft_getenv_addr(char *name, char **ms_envp)
{
	size_t	len;
	int		i;

	if (!name || !ms_envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (ms_envp[i])
	{
		if (ft_strncmp(name, ms_envp[i], len) == 0 && ms_envp[i][len] == '=')
			return (ms_envp + i);
		i++;
	}
	return (NULL);
}

char	*ft_getenv(char *name, char **ms_envp)
{
	char	**env_addr;
	char	*value;

	env_addr = ft_getenv_addr(name, ms_envp);
	if (!env_addr)
		return (NULL);
	value = (*env_addr) + ft_strlen(name);
	if (*value == '=')
	{
		value++;
		return (value);
	}
	else
		return (NULL);
}

void	ft_set_env(char *name, char *value, char **ms_envp)
{
	char	*res;
	char	*tmp;
	char	**env_addr;
	size_t	name_len;

	if (!name || !value || !ms_envp || !*ms_envp)
		return ;
	name_len = 0;
	env_addr = ft_getenv_addr(name, ms_envp);
	if (!env_addr)
		return ;
	while ((*env_addr)[name_len] && (*env_addr)[name_len] != '=')
		name_len++;
	if ((*env_addr)[name_len] == '=')
		name_len++;
	else
		return ;
	tmp = ft_substr(*env_addr, 0, name_len);
	res = ft_strjoin(tmp, value);
	free(tmp);
	tmp = *env_addr;
	*env_addr = res;
	free(tmp);
}

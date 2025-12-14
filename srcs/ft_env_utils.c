/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:23:25 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/14 15:46:51 by lseabra-         ###   ########.fr       */
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

static char	*ft_get_name_with_equal(char **env_addr)
{
	size_t	name_len;

	if (!env_addr || !*env_addr)
		return (0);
	name_len = 0;
	while ((*env_addr)[name_len] && (*env_addr)[name_len] != '=')
		name_len++;
	if ((*env_addr)[name_len] == '=')
		name_len++;
	return (ft_substr(*env_addr, 0, name_len));
}

void	ft_set_env(t_data *dt, char *name, char *value)
{
	char	*res;
	char	*tmp;
	char	**env_addr;

	if (!name || !value || !dt || !dt->ms_envp)
		return ;
	env_addr = ft_getenv_addr(name, dt->ms_envp);
	if (!env_addr)
	{
		dt->ms_envp = ft_expand_envp(dt->ms_envp);
		env_addr = dt->ms_envp;
		while (*env_addr)
			env_addr++;
		tmp = ft_strjoin(name, "=");
	}
	else
		tmp = ft_get_name_with_equal(env_addr);
	res = ft_strjoin_free(tmp, true, value, false);
	tmp = *env_addr;
	*env_addr = res;
	if (tmp)
		free(tmp);
}

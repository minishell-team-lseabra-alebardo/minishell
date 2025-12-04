/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:23:25 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/04 13:07:23 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

/**
 * @brief Retrieves the address of an environment variable entry.
 *
 * Searches the minishell environment array for a variable matching @p name.
 * If found, a pointer to the corresponding array element is returned,
 * allowing the caller to modify or replace the entry.
 *
 * @param name    The variable name to search for.
 * @param ms_envp The minishell's environment array.
 * @return A pointer to the matching entry in ms_envp, or NULL if not found.
 */
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

/**
 * @brief Retrieves the value of an environment variable.
 *
 * Locates the entry for @p name in the minishell environment and returns
 * a pointer to the value portion (the characters after the '='). If the
 * variable is not found or has no value, NULL is returned.
 *
 * @param name    The environment variable name.
 * @param ms_envp The minishell's environment array.
 * @return A pointer to the variable's value, or NULL if unavailable.
 */
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

/**
 * @brief Updates the value of an existing environment variable.
 *
 * Searches for @p name in the minishell environment and replaces its value
 * with the provided @p value. The entry is rebuilt as "name=value".
 * This function updates variables but does not create new ones.
 *
 * @param name    The variable name to modify.
 * @param value   The new value to assign.
 * @param ms_envp The minishell's environment array.
 */
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

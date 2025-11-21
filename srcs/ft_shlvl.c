/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 21:52:38 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/21 18:51:32 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static char	*ft_find_shlvl(char **ms_envp)
{
	int		i;

	i = 0;
	while (ms_envp[i] && ft_strncmp("SHLVL=", ms_envp[i], 6))
		i++;
	if (!ms_envp[i])
		return (0);
	return (ms_envp[i]);
}

static void	ft_change_shlvl(char *new_shlvl, char **ms_envp)
{
	int		i;

	i = 0;
	while (ms_envp[i] && ft_strncmp("SHLVL=", ms_envp[i], 6))
		i++;
	free(ms_envp[i]);
	ms_envp[i] = new_shlvl;
}

static int	ft_new_shlvl(t_data *dt)
{
	int		i;

	dt->ms_envp = ft_expand_envp(dt->ms_envp);
	if (!dt->ms_envp)
		return (-1);
	i = 0;
	while (dt->ms_envp[i])
		i++;
	dt->ms_envp[i] = (char *) ft_calloc(18, sizeof(char));
	if (!dt->ms_envp[i])
		return (-1);
	ft_strlcpy(dt->ms_envp[i], "SHLVL=1", 8);
	return (0);
}

int	ft_shlvl(t_data *dt)
{
	char	*shlvl_var;
	char	*new_shlvl;
	int		shlvl_value;

	shlvl_var = ft_find_shlvl(dt->ms_envp);
	if (!shlvl_var)
		return (ft_new_shlvl(dt));
	shlvl_value = ft_atoi(shlvl_var + 6);
	if (shlvl_value < INT_MAX)
		shlvl_value++;
	new_shlvl = (char *) ft_calloc(18, sizeof(char));
	if (!new_shlvl)
		return (-1);
	ft_strlcpy(new_shlvl, "SHLVL=", 7);
	shlvl_var = ft_itoa(shlvl_value);
	ft_strlcat(new_shlvl, shlvl_var, 18);
	free(shlvl_var);
	ft_change_shlvl(new_shlvl, dt->ms_envp);
	return (0);
}

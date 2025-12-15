/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:20:27 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/15 13:44:19 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static bool	ft_validate_var(char *var)
{
	int	i;

	i = 0;
	while (var[i] && ft_isalpha(var[i]))
		i++;
	if (!ft_isalpha(var[i]) && (i == 0 || (var[i] != '=' && var[i] != '\0')))
		return (false);
	else
		return (true);
}

static char	**ft_get_var_addr(char *var, char **ms_envp)
{
	size_t	i;
	char	*name;
	char	**addr;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	name = ft_substr(var, 0, i);
	addr = ft_getenv_addr(name, ms_envp);
	free(name);
	return (addr);
}

static size_t	ft_count_new_vars(char **args, char **ms_envp)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	i = 0;
	while (args[i])
	{
		if (ft_validate_var(args[i]) && !ft_get_var_addr(args[i], ms_envp))
			counter++;
		i++;
	}
	return (counter);
}

static int	ft_add_var(char *arg, char **ms_envp, size_t *envp_len)
{
	char	**env_addr;

	if (!ft_validate_var(arg))
	{
		ft_puterror("export", arg, ERR_INV_ID);
		return (EXIT_FAILURE);
	}
	env_addr = ft_get_var_addr(arg, ms_envp);
	if (env_addr)
	{
		free(*env_addr);
		*env_addr = ft_strdup(arg);
	}
	else
	{
		ms_envp[*envp_len] = ft_strdup(arg);
		(*envp_len)++;
	}
	return (EXIT_SUCCESS);
}

int	ft_export_vars(char	**args, t_data *dt, size_t	envp_len)
{
	size_t	new_var_counter;
	int		status;
	char	**new_envp;

	new_var_counter = ft_count_new_vars(args, dt->ms_envp);
	status = EXIT_SUCCESS;
	if (new_var_counter > 0)
	{
		new_envp = ft_calloc(envp_len + new_var_counter + 1, sizeof(char *));
		if (!new_envp)
			return (EXIT_FAILURE);
		ft_memcpy(new_envp, dt->ms_envp, envp_len * sizeof(char *));
		free(dt->ms_envp);
		dt->ms_envp = new_envp;
	}
	while (*args)
	{
		if (ft_add_var(*args, dt->ms_envp, &envp_len) != EXIT_SUCCESS)
			status = EXIT_FAILURE;
		args++;
	}
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:31:20 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/01 19:49:33 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	ft_strcmp_all(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	max_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len >= s2_len)
		max_len = s1_len;
	else
		max_len = s2_len;
	return (ft_strncmp(s1, s2, max_len));
}

static void	ft_strarr_bubble_sort(char **strarr, size_t len)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	if (!strarr)
		return ;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp_all(strarr[j], strarr[j + 1]) > 0)
			{
				tmp = strarr[j];
				strarr[j] = strarr[j + 1];
				strarr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	ft_print_formatted_env(char *env)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!env)
		return ;
	res = ft_calloc(ft_strlen(EXP_PREFIX) + ft_strlen(env) + 4, sizeof(char));
	if (!res)
		return ;
	i = ft_strlcpy(res, EXP_PREFIX, ft_strlen(EXP_PREFIX) + 1);
	j = 0;
	while (env[j] && env[j] != '=')
		j++;
	ft_strlcpy(res + i, env, j + 1);
	i += j;
	if (env[j] == '=')
	{
		i += ft_strlcpy(res + i, "=\"", 2 + 1);
		i += ft_strlcpy(res + i, env + j + 1, ft_strlen(env) + 1);
		i += ft_strlcpy(res + i, "\"", 1 + 1);
	}
	i += ft_strlcpy(res + i, "\n", 1 + 1);
	write(STDOUT_FILENO, res, ft_strlen(res));
	free(res);
}

static int	ft_print_ordered_env(char **strarr)
{
	char	**ordered;
	size_t	i;

	if (!strarr)
		return (EXIT_FAILURE);
	i = 0;
	while (strarr[i])
		i++;
	ordered = ft_calloc(i + 1, sizeof(char *));
	if (!ordered)
		return (EXIT_FAILURE);
	ft_memcpy(ordered, strarr, i * sizeof(char *));
	ft_strarr_bubble_sort(ordered, i);
	i = 0;
	while (ordered[i])
	{
		ft_print_formatted_env(ordered[i]);
		i++;
	}
	free(ordered);
	return (EXIT_SUCCESS);
}

static bool	ft_validate_var(char *var)
{
	int	i;

	i = 0;
	while (var[i] && ft_isalpha(var[i]))
		i++;
	if (!ft_isalpha(var[i]) && (i == 0 || var[i] != '='))
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

static size_t	ft_get_envp_len(char **ms_envp)
{
	size_t	i;

	if (!ms_envp)
		return (0);
	i = 0;
	while (ms_envp[i])
		i++;
	return (i);
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

static int	ft_export_vars(char	**args, t_data *dt)
{
	size_t	new_var_counter;
	size_t	envp_len;
	int		status;
	char	**new_envp;

	new_var_counter = ft_count_new_vars(args, dt->ms_envp);
	envp_len = ft_get_envp_len(dt->ms_envp);
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

int	ft_export(t_cmd *cmd, t_data *dt)
{
	if (!cmd || !cmd->args || !dt->ms_envp)
		return (EXIT_FAILURE);
	else if (cmd->args[1] && !ft_is_in_pipeline(cmd))
		return (ft_export_vars(cmd->args + 1, dt));
	else if (cmd->args[0])
		return (ft_print_ordered_env(dt->ms_envp));
	return (EXIT_SUCCESS);
}

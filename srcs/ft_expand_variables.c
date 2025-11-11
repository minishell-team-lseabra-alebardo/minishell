/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:14:48 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/11 14:36:01 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_copy_rest(char *new_arg, char *src)
{
	while (*new_arg)
		new_arg++;
	while (src && *src)
	{
		*new_arg = *src;
		new_arg++;
		src++;
	}
}

static char	*ft_copy_var_value(char *env_var, char *arg, int var_size)
{
	char	*new_arg;
	int		env_var_len;
	int		i;

	env_var_len = 0;
	if (env_var && *env_var)
	{
		while (*env_var != '=')
			env_var++;
		env_var++;
		env_var_len = ft_strlen(env_var);
	}
	new_arg = ft_calloc((ft_strlen(arg) + env_var_len) - var_size + 1, 1);
	if (!new_arg)
		return (0);
	i = ft_copy_start(new_arg, arg);
	ft_copy_rest(new_arg, env_var);
	i += var_size;
	ft_copy_rest(new_arg, &arg[i]);
	return (new_arg);
}

static char	*ft_expand_variable(char **ms_envp, char *arg, int i)
{
	char	*var_name;
	char	*new_arg;
	int		var_size;

	var_size = ft_var_size(&arg[i]);
	var_name = (char *) ft_calloc(var_size + 1, 1);
	if (!var_name)
		return (arg);
	ft_copy_var_name(&arg[i], var_name);
	while (*ms_envp && ft_strncmp(*ms_envp, var_name, var_size))
		ms_envp++;
	free(var_name);
	new_arg = ft_copy_var_value(*ms_envp, arg, var_size);
	if (!new_arg)
		return (arg);
	free(arg);
	return (new_arg);
}

static char	*ft_search_variable(char **ms_envp, char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			i++;
			i = ft_skip_single_quotes(arg, i);
		}
		if (arg[i] == '$' && !ft_is_whitespace(arg[i]))
		{
			arg = ft_expand_variable(ms_envp, arg, ++i);
			while (!ft_is_whitespace(arg[i]))
				i++;
		}
		if (arg[i])
			i++;
	}
	return (arg);
}

void	ft_args_treament(char **args, char **ms_envp)
{
	while (*args)
	{
		*args = ft_search_variable(ms_envp, *args);
		ft_search_quotes(*args);
		args++;
	}
}

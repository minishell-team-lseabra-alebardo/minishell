/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:14:48 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/09 14:21:25 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_copy_rest(char *new_arg, char *src)
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

static char	*ft_copy_var_value(char *env_var, char *arg, int var_size, int *i)
{
	char	*new_arg;
	int		env_var_len;
	int		j;

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
	j = ft_copy_start(new_arg, arg, *i);
	ft_copy_rest(new_arg, env_var);
	j += var_size;
	ft_copy_rest(new_arg, &arg[j]);
	*i += env_var_len - 1;
	return (new_arg);
}

char	*ft_expand_variable(char **ms_envp, t_data *dt, char *arg, int *i)
{
	char	*var_name;
	char	*new_arg;
	int		var_size;

	*i += 1;
	if (!ft_strncmp("?", &arg[*i], 1))
		return (ft_copy_lst_stat(dt->last_status, arg, i));
	var_size = ft_var_size(&arg[*i]);
	var_name = (char *) ft_calloc(var_size + 1, 1);
	if (!var_name)
		return (arg);
	ft_copy_var_name(&arg[*i], var_name);
	while (*ms_envp && ft_strncmp(*ms_envp, var_name, var_size))
		ms_envp++;
	free(var_name);
	new_arg = ft_copy_var_value(*ms_envp, arg, var_size, i);
	if (!new_arg)
		return (arg);
	free(arg);
	return (new_arg);
}

static char	*ft_search_variable(t_data *dt, char *arg, int mode)
{
	int		i;
	char	quote;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || (arg[i] == '\"' && mode == 0))
		{
			quote = arg[i];
			i++;
			i = ft_avoid_quotes(arg, quote, i);
		}
		if (arg[i] == '(')
		{
			while (arg[i] != ')')
				i++;
		}
		if (arg[i] == '$' && !ft_is_whitespace(arg[i + 1]))
			arg = ft_expand_variable(dt->ms_envp, dt, arg, &i);
		else
			i++;
	}
	return (arg);
}

void	ft_args_treatment(char **args, t_data *dt, int mode)
{
	char	**split_line;

	if (mode == 0)
	{
		*args = ft_prep_lst_stat(*args);
		*args = ft_search_variable(dt, *args, mode);
		*args = ft_wildcards(*args);
	}
	else
	{
		split_line = dt->split_line;
		while (*args)
		{
			while (ft_strncmp(*split_line, *args, ft_strlen(*args)))
				split_line++;
			*args = ft_search_quotes(dt, *args);
			if (ft_strncmp(*split_line, *args, ft_strlen(*args)))
				*split_line = *args;
			args++;
		}
	}
}

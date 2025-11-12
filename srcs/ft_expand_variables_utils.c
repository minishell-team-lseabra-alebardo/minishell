/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_variables_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:18:09 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/12 01:04:10 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	ft_is_whitespace(char c)
{
	if (!c || (c == ' ' || (c >= '\t' && c <= '\r')))
		return (1);
	return (0);
}

int	ft_avoid_quotes(char *arg, char quote, int i)
{
	while (arg[i] && arg[i] != quote)
		i++;
	return (i++);
}

int	ft_var_size(char *arg)
{
	int		i;

	i = 0;
	while (!ft_is_whitespace(arg[i]) && arg[i] != '\'' && arg[i] != '\"')
		i++;
	return (++i);
}

void	ft_copy_var_name(char *arg, char *var_name)
{
	int		i;

	i = 0;
	while (!ft_is_whitespace(arg[i]) && arg[i] != '\'' && arg[i] != '\"')
	{
		var_name[i] = arg[i];
		i++;
	}
	var_name[i] = '=';
}

int	ft_copy_start(char *new_arg, char *arg)
{
	int		i;

	i = 0;
	while (arg[i] != '$')
	{
		if (arg[i] == '\'')
		{
			new_arg[i] = arg[i];
			i++;
			while (arg[i] != '\'')
			{
				new_arg[i] = arg[i];
				i++;
			}
		}
		new_arg[i] = arg[i];
		i++;
	}
	return (i);
}

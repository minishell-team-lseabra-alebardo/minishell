/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:37:39 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/05 23:01:43 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_move_chars(char *arg)
{
	while (*arg)
	{
		ft_memmove(arg, arg + 1, 1);
		arg++;
	}
}

static char	*ft_search_variables(t_data *dt, char *arg, char quote, int *i)
{
	while (arg[*i] != quote)
	{
		if (quote == '\"'
			&& (arg[*i] == '$' && !ft_is_whitespace(arg[*(i) + 1])))
			arg = ft_expand_variable(dt->ms_envp, arg, i);
		else
			*i += 1;
	}
	return (arg);
}

char	*ft_search_quotes(t_data *dt, char *arg)
{
	int		i;
	char	quote;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			quote = arg[i];
			while (arg[i] == quote)
			{
				ft_move_chars(&arg[i]);
				arg = ft_search_variables(dt, arg, quote, &i);
				ft_move_chars(&arg[i]);
			}
		}
		else
			i++;
	}
	return (arg);
}

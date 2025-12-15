/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:41:57 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/15 16:55:39 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	ft_avoid_heredoc(char *arg, int i)
{
	char	quote;

	i += 2;
	while (ft_is_whitespace(arg[i]))
		i++;
	while (!ft_is_whitespace(arg[i]))
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			quote = arg[i];
			i++;
			i = ft_avoid_quotes(arg, quote, i);
		}
		i++;
	}
	return (i);
}

static void	ft_move_chars(char *arg)
{
	while (*arg)
	{
		ft_memmove(arg, arg + 1, 1);
		arg++;
	}
}

char	*ft_sq_hdoc(char *arg)
{
	int		i;
	char	quote;

	i = 0;
	if (arg[i] == '(')
		return (arg);
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			quote = arg[i];
			while (arg[i] == quote)
			{
				ft_move_chars(&arg[i]);
				while (arg[i] != quote)
					i++;
				ft_move_chars(&arg[i]);
			}
		}
		else
			i++;
	}
	return (arg);
}

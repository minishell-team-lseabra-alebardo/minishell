/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:54:57 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/04 21:55:13 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static int	ft_move_chars(char *arg, char quote, int i)
{
	int		j;

	j = i;
	while (arg[j])
	{
		arg[j] = arg[j + 1];
		j++;
	}
	while (arg[i] != quote)
		i++;
	j = i;
	while (arg[j])
	{
		arg[j] = arg[j + 1];
		j++;
	}
	return (i);
}

static void	ft_search_quotes(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
			i = ft_move_chars(arg, arg[i], i);
		else
			i++;
	}
}

void	ft_remove_quotes(char **args)
{
	while (*args)
	{
		ft_search_quotes(*args);
		args++;
	}
}

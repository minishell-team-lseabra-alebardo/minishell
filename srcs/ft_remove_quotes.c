/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:37:39 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/04 17:59:30 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_move_chars(char *arg, char quote)
{
	ft_memmove(arg, arg + 1, 1);
	arg++;
	while (*arg != quote)
	{
		ft_memmove(arg, arg + 1, 1);
		arg++;
	}
	ft_memmove(arg, arg + 1, 1);
	arg++;
	while (*arg)
	{
		ft_memmove(arg, arg + 1, 1);
		arg++;
	}
}

static void	ft_search_quotes(char *arg)
{
	while (*arg)
	{
		if (*arg == '\'' || *arg == '\"')
			ft_move_chars(arg, *arg);
		arg++;
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

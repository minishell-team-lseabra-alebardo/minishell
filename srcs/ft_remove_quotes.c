/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:37:39 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/11 22:40:15 by alebarbo         ###   ########.fr       */
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

void	ft_search_double_quotes(char *arg)
{
	while (*arg)
	{
		while (*arg == '\"')
		{
			ft_move_chars(arg);
			while (*arg != '\"')
				arg++;
			ft_move_chars(arg);
		}
		arg++;
	}
}

void	ft_search_single_quotes(char *arg)
{
	while (*arg)
	{
		while (*arg == '\'')
		{
			ft_move_chars(arg);
			while (*arg != '\'')
				arg++;
			ft_move_chars(arg);
		}
		arg++;
	}
}

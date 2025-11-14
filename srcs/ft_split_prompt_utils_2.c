/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_prompt_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:31:50 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/14 16:42:46 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	ft_calc_jump(const char *s)
{
	int	counter;

	counter = 0;
	if (*s && ft_strchr("\'\"", *s))
		counter += ft_quote_len(s);
	else if (*s == '(')
		counter += ft_parenthesis_len(s);
	return (counter);
}

bool	ft_check_n_back(const char *str)
{
	if (!str)
		return (false);
	str--;
	while (*str && !ft_strchr(WS_POSIX, *str))
	{
		if (!ft_isdigit(*str))
			return (false);
		str--;
	}
	return (true);
}

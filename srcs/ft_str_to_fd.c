/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:06:42 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/16 19:24:18 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	ft_str_to_fd(char *str)
{
	intmax_t	res;
	size_t		i;

	if (!str)
		return (-1);
	res = 0;
	i = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		res = (res * 10) + str[i] - '0';
		if (res >= 1024)
			return (-1);
		i++;
	}
	return ((int)res);
}

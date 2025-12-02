/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:30:59 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/02 16:42:21 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_echo(char **args)
{
	int		i;
	int		flag_n;

	i = 1;
	flag_n = ft_strncmp(args[1], "-n", 3);
	if (!flag_n)
		i++;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (flag_n)
		printf("\n");
}
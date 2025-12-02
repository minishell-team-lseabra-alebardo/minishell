/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:10:33 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/02 15:20:39 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_env(char **ms_envp)
{
	int		i;
	int		j;

	i = 0;
	while (ms_envp[i])
	{
		j = 0;
		while (ms_envp[i][j])
		{
			if (ms_envp[i][j] == '=')
			{
				printf("%s\n", ms_envp[i]);
				break ;
			}
			j++;
		}
		i++;
	}
}
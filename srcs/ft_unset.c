/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:51:58 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/02 22:13:21 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_unset(t_data *dt, char **args)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (dt->ms_envp[j])
		{
			if (!ft_strncmp(args[i], dt->ms_envp[j], ft_strlen(args[i]))
				&& (dt->ms_envp[j][ft_strlen(args[i])] == '='
				|| !dt->ms_envp[j][ft_strlen(args[i])]))
			{
				temp = dt->ms_envp[j];
				while (dt->ms_envp[j])
				{
					dt->ms_envp[j] = dt->ms_envp[j + 1];
					j++;
				}
				free(temp);
				break ;
			}
			j++;
		}
		i++;
	}
}
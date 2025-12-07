/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:51:58 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/05 23:16:17 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_remove_variable(t_data *dt, int j)
{
	char	*temp;

	temp = dt->ms_envp[j];
	while (dt->ms_envp[j])
	{
		dt->ms_envp[j] = dt->ms_envp[j + 1];
		j++;
	}
	free(temp);
}

int	ft_unset(t_data *dt, char **args)
{
	int		i;
	int		j;

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
				ft_remove_variable(dt, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

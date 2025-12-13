/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:15:30 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/13 21:05:45 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

char	**ft_expand_envp(char **ms_envp)
{
	char	**expanded_envp;
	int		i;

	i = 0;
	while (ms_envp[i])
		i++;
	expanded_envp = (char **) ft_calloc(i + 2, sizeof(char *));
	if (!expanded_envp)
		return (0);
	i = 0;
	while (ms_envp[i])
	{
		expanded_envp[i] = ms_envp[i];
		i++;
	}
	free(ms_envp);
	return (expanded_envp);
}

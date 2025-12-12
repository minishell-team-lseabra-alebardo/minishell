/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:30:54 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/12 15:17:27 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

char	**ft_strarr_dup(char **strarr)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (strarr[i])
		i++;
	new_arr = ft_calloc(i + 1, sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (strarr[i])
	{
		new_arr[i] = ft_strdup(strarr[i]);
		if (!new_arr[i])
		{
			while (--i >= 0)
				free(new_arr[i]);
			free(new_arr);
			return (NULL);
		}
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

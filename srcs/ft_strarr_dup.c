/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:30:54 by lseabra-          #+#    #+#             */
/*   Updated: 2025/10/24 12:21:43 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

/**
 * @brief Creates a deep copy of a NULL-terminated array of strings.
 *
 * The ft_strarr_dup function allocates memory for a new array and creates
 * duplicates of each string in the original array. The resulting array is
 * NULL-terminated and completely independent from the source array. Both
 * the array structure and individual strings are newly allocated.
 *
 * @param strarr Pointer to the NULL-terminated array of strings to copy.
 * @return A newly allocated array containing duplicates of all strings
 *         from the original array, or NULL if memory allocation fails.
 *         The caller is responsible for freeing the array and its
 *         elements.
 */
char	**ft_strarr_dup(char **strarr)
{
	size_t	i;
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

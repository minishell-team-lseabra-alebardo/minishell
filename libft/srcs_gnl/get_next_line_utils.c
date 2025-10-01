/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:39:29 by lseabra-          #+#    #+#             */
/*   Updated: 2025/08/25 14:33:12 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/libft.h"
#include <stdint.h>
#include <stdlib.h>

/**
 * @function ft_linelen
 * @brief Calculates the length of a line in a string.
 *
 * The `ft_linelen` function computes the length of a line in the given string
 * `s`, stopping at the first newline character (`\n`) or the null terminator.
 * If a newline character is encountered, it is included in the count.
 *
 * @param s The string to calculate the line length from.
 * @return The length of the line, including the newline character if present.
 */
size_t	ft_linelen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	if (s && s[i] == '\n')
		i++;
	return (i);
}

/**
 * @function ft_bufferlinejoin
 * @brief Joins a line and a buffer into a single string.
 *
 * The `ft_bufferlinejoin` function concatenates the contents of `line` and
 * `buffer` into a newly allocated string. The function ensures that the
 * resulting string includes all characters from both inputs and is
 * null-terminated. The caller is responsible for freeing the memory allocated
 * for the result.
 *
 * @param line The first string to join. Can be `NULL`.
 * @param buffer The second string to join. Can be `NULL`.
 * @return A pointer to the newly allocated string containing the concatenated
 *         result of `line` and `buffer`. Returns `NULL` if memory allocation
 *         fails.
 */
char	*ft_bufferlinejoin(char *line, char *buffer)
{
	size_t	line_len;
	size_t	buffer_len;
	size_t	i;
	char	*res;

	line_len = ft_linelen(line);
	buffer_len = ft_linelen(buffer);
	res = ft_calloc(line_len + buffer_len + 1, sizeof(char));
	if (!res)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (i < line_len)
	{
		res[i] = line[i];
		i++;
	}
	i--;
	while (++i < line_len + buffer_len)
		res[i] = buffer[i - line_len];
	free(line);
	return (res);
}

/**
 * @function ft_haschar
 * @brief Checks if a character exists in a string.
 *
 * The `ft_haschar` function checks if the character `c` exists in the string
 * `s`. If the character `c` is found, the function returns `1`. Otherwise, it
 * returns `0`.
 *
 * @param s The string to search in. Must be null-terminated.
 * @param c The character to locate, passed as an `int` but interpreted as
 *          `char`.
 * @return `1` if the character `c` is found in `s`, or `0` if it is not found.
 */
int	ft_haschr(char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

/**
 * @function ft_cleanbuffer
 * @brief Cleans up a buffer after extracting a line.
 *
 * The `ft_cleanbuffer` function removes the characters of the current line,
 * including the newline character (`\n`), from the buffer. It shifts the
 * remaining characters in the buffer to the beginning and fills the rest with
 * null terminators.
 *
 * @param buffer The buffer to clean. Must be a null-terminated string.
 *
 * @note
 * - If the buffer is `NULL`, the function does nothing.
 * - The function modifies the buffer in place.
 */
void	ft_cleanbuffer(char *buffer)
{
	int		i;
	int		j;

	if (!buffer)
		return ;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i + j])
	{
		buffer[j] = buffer[i + j];
		j++;
	}
	while (buffer[j])
	{
		buffer[j] = '\0';
		j++;
	}
}

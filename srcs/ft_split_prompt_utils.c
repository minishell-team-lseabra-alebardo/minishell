/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_prompt_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:16:59 by lseabra-          #+#    #+#             */
/*   Updated: 2025/10/28 15:45:49 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

bool	ft_is_op(const char *s, const char *op)
{
	if (!s || !*s || !op)
		return (false);
	if (ft_strncmp(s, op, ft_strlen(op) + 1) == 0)
		return (true);
	else
		return (false);
}

int	ft_get_op_len(const char *s)
{
	if (!s)
		return (0);
	else if (ft_is_op(s, CMD_AND))
		return ((int)ft_strlen(CMD_AND));
	else if (ft_is_op(s, CMD_OR))
		return ((int)ft_strlen(CMD_OR));
	else if (ft_is_op(s, CMD_PIPE))
		return ((int)ft_strlen(CMD_PIPE));
	else if (ft_is_op(s, CMD_HEREDOC))
		return ((int)ft_strlen(CMD_HEREDOC));
	else if (ft_is_op(s, CMD_IN))
		return ((int)ft_strlen(CMD_IN));
	else if (ft_is_op(s, CMD_OUT_APPEND))
		return ((int)ft_strlen(CMD_OUT_APPEND));
	else if (ft_is_op(s, CMD_OUT))
		return ((int)ft_strlen(CMD_OUT));
	else
		return (0);
}

/**
 * @brief Calculates the length of a quoted string segment.
 *
 * The ft_quote_length function determines the length of a quoted segment
 * starting from the given position in the string. It counts from the
 * opening quote character until it finds the matching closing quote, or
 * reaches the end of the string. The returned length includes both the
 * opening and closing quote characters. If the string does not start with
 * a quote character (' or "), the function returns 0.
 *
 * @param s Pointer to the string to be evaluated.
 * @return The total length including both quote characters, length until
 *         the end of string if no closing quote is found, or 0 if the
 *         string does not start with a quote character.
 */
size_t	ft_quote_len(const char *s)
{
	size_t	len;
	char	quote;

	if (!ft_strchr("\'\"", s[0]))
		return (0);
	quote = s[0];
	len = 1;
	while (s[len] && quote != s[len])
		len++;
	return (len + 1);
}

/**
 * @brief Calculates the length of a string enclosed by parentheses.
 *
 * The ft_parenthesis_len function determines the length of a segment enclosed
 * by parentheses starting from the given position in the string. It counts from
 * the opening parenthesis character until it finds the matching closing 
 * parenthesis, or reaches the end of the string. The returned length includes
 * both the opening and closing parenthesis characters. If the string does not 
 * start with an opening parenthesis character '(', the function returns 0.
 *
 * @param s Pointer to the string to be evaluated.
 * @return The total length including both parenthesis characters, length until
 *         the end of string if no closing parenthesis is found, or 0 if the
 *         string does not start with an opening parenthesis character.
 */
size_t	ft_parenthesis_len(const char *s)
{
	size_t	len;
	size_t	counter;

	if (s[0] != '(')
		return (0);
	len = 1;
	counter = 1;
	while (s[len] && counter > 0)
	{
		if (s[len] == '(')
			counter++;
		else if (s[len] == ')')
			counter--;
		len++;
	}
	return (len);
}

/**
 * @brief Frees a partially allocated array of strings.
 *
 * The ft_free_strarr function deallocates memory for an array of strings up to a
 * specified position. It iterates through the array, freeing each individual
 * string pointer, and then frees the array itself. This is typically used for
 * cleanup when an allocation fails during array construction.
 *
 * @param arr Pointer to the array of strings to be freed.
 * @param position The number of elements to free (0-indexed).
 * @return Always returns NULL (0) for convenient error handling.
 */
char	**ft_free_strarr(char **arr, size_t position)
{
	size_t	i;

	i = 0;
	while (i < position)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

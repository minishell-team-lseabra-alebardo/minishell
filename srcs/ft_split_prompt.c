/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:10:56 by lseabra-          #+#    #+#             */
/*   Updated: 2025/10/27 10:14:05 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static int	ft_calc_jump(const char *s)
{
	int	counter;

	counter = 0;
	if (*s && ft_strchr("\'\"", *s))
		counter += ft_quote_len(s);
	else if (*s == '(')
		counter += ft_parenthesis_len(s);
	return (counter);
}

static bool	ft_check_n_back(const char *str)
{
	if (!str)
		return (false);
	str--;
	while (*str && !ft_strchr(WS_POSIX, *str))
	{
		if (!ft_isdigit(*str))
			return (false);
		str--;
	}
	return (true);
}

/**
 * @brief Counts the number of words in a string, respecting quoted segments.
 *
 * The ft_count_words function parses a string and counts the number of words
 * separated by delimiter characters specified in seps. Quoted segments (using
 * single or double quotes) are treated as single units regardless of delimiters
 * inside them. Leading delimiters are skipped, and the function properly 
 * handles transitions between words and delimiters.
 *
 * @param s Pointer to the null-terminated string to be parsed.
 * @param seps Pointer to a string containing delimiter characters.
 * @return The total number of words found in the string.
 */
static size_t	ft_count_words(const char *s, char *seps)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i] && ft_strchr(seps, s[i]))
		i++;
	while (s[i])
	{
		if ((s[i] && ft_strchr("\'\"", s[i])) || (s[i] == '('))
			i += ft_calc_jump(s + i);
		else if (ft_get_op_len(s + i) > 0)
		{
			counter += (i > 0 && !ft_strchr(seps, s[i - 1]) && !ft_check_n_back(s + i));
			i += ft_get_op_len(s + i);
			counter += (s[i] && !ft_strchr(seps, s[i]));
		}
		else if (i > 0 && ft_strchr(seps, s[i]) && !ft_strchr(seps, s[i++ - 1]))
			counter++;
		else
			i++;
	}
	return (counter + (i > 0 && (!ft_strchr(seps, s[i - 1]))));
}

/**
 * @brief Extracts and allocates a single word from the string.
 *
 * The ft_process_word function extracts one word from the current position in 
 * the string, treating quoted segments as single units regardless of delimiters
 * inside them. It allocates memory for the extracted word and advances the
 * string pointer past the processed word. The extraction stops when a delimiter
 * character (not inside quotes) is encountered.
 *
 * @param s Pointer to a pointer to the current position in the string (updated
 *          after extraction).
 * @param seps Pointer to a string containing delimiter characters.
 * @return A newly allocated string containing the extracted word, or NULL if
 *         memory allocation fails.
 */
static char	*ft_process_word(const char **s, char *seps)
{
	int		i;
	char	*word;

	i = 0;
	while (ft_isdigit((*s)[i]))
		i++;
	if (ft_get_op_len(*s + i) > 0)
		i += ft_get_op_len(*s + i);
	while (ft_isdigit((*s)[i]))
		i++;
	if (ft_isop(*s + i) > 0)
		i += ft_isop(*s + i);
	else
	{
		while ((*s)[i] && (!ft_strchr(seps, (*s)[i])) && (!ft_isop(*s + i)))
		{
			if ((*s)[i] && ft_strchr("\'\"", (*s)[i]))
				i += ft_quote_len((*s) + i);
			else if ((*s)[i] == '(')
				i += ft_parenthesis_len((*s) + i);
			else
				i++;
		}
	}
	word = ft_calloc((i + 1), sizeof(char));
	if (!word)
		return (NULL);
	ft_memmove(word, *s, i);
	*s += i;
	return (word);
}

/**
 * @brief Splits a string into an array of words, respecting quoted segments.
 *
 * The ft_split_prompt function parses a string and splits it into an array
 * of words based on delimiter characters specified in seps. Quoted segments
 * (using single or double quotes) are preserved as single words, including
 * the quote characters themselves. Multiple consecutive delimiters are
 * treated as one, and leading/trailing delimiters are ignored. The resulting
 * array is NULL-terminated.
 *
 * @param s Pointer to the null-terminated string to be split.
 * @param seps Pointer to a string containing delimiter characters.
 * @return A newly allocated NULL-terminated array of strings, where each
 *         element is a word from the original string. Returns NULL if
 *         memory allocation fails. The caller is responsible for freeing
 *         the array and its elements.
 */
char	**ft_split_prompt(const char *s, char *seps)
{
	size_t	word_count;
	size_t	i;
	char	**arr;

	word_count = ft_count_words(s, seps);
	arr = ft_calloc((word_count + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < word_count)
	{
		while (ft_strchr(seps, *s) && !ft_strchr("\'\"", *s))
			s++;
		arr[i] = ft_process_word(&s, seps);
		if (!arr[i])
			return (ft_free_strarr(arr, i));
	}
	if (arr[0] != NULL)
		arr[word_count] = NULL;
	return (arr);
}

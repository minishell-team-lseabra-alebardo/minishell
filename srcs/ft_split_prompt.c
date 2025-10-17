/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:10:56 by lseabra-          #+#    #+#             */
/*   Updated: 2025/10/17 23:25:32 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static int	ft_isop(const char *s)
{
	if (!ft_strchr(CMD_ALL, *s))
		return (0);
	if (ft_strncmp(s, CMD_AND, ft_strlen(CMD_AND)) == 0)
		return ((int)ft_strlen(CMD_AND));
	else if (ft_strncmp(s, CMD_OR, ft_strlen(CMD_OR)) == 0)
		return ((int)ft_strlen(CMD_OR));
	else if (ft_strncmp(s, CMD_PIPE, ft_strlen(CMD_PIPE)) == 0)
		return ((int)ft_strlen(CMD_PIPE));
	else if (ft_strncmp(s, CMD_HEREDOC, ft_strlen(CMD_HEREDOC)) == 0)
		return ((int)ft_strlen(CMD_HEREDOC));
	else if (ft_strncmp(s, CMD_IN, ft_strlen(CMD_IN)) == 0)
		return ((int)ft_strlen(CMD_IN));
	else if (ft_strncmp(s, CMD_OUT_APPEND, ft_strlen(CMD_OUT_APPEND)) == 0)
		return ((int)ft_strlen(CMD_OUT_APPEND));
	else if (ft_strncmp(s, CMD_OUT, ft_strlen(CMD_OUT)) == 0)
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
static size_t	ft_quote_len(const char *s)
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
static size_t	ft_parenthesis_len(const char *s)
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
		if (s[i] && ft_strchr("\'\"", s[i]))
			i += ft_quote_len(s + i);
		else if (s[i] == '(')
			i += ft_parenthesis_len(s + i);
		else if (ft_isop(s + i) > 0)
		{
			counter += (i > 0 && !ft_strchr(seps, s[i - 1]));
			i += ft_isop(s + i);
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
static char	**ft_free_strarr(char **arr, size_t position)
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
	if (ft_isop(*s + i) > 0)
		i += ft_isop(*s + i);
	else
	{
		while ((*s)[i] && (!ft_strchr(seps, (*s)[i])) && ft_isop(*s + i) == 0)
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

// int	main(int argc, char **argv)
// {
// 	int	counter;

// 	if (argc != 2)
// 		return (1);
// 	counter = ft_count_words(argv[1], WS_POSIX);
// 	ft_printf("%s\nwords: %d\n", argv[1], counter);
// }
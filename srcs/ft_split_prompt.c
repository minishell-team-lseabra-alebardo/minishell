/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:10:56 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/12 15:17:18 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_handle_operator(size_t *i, char *s, char *seps, size_t *counter)
{
	if ((*i > 0 && !ft_strchr(seps, s[*i - 1]) && !ft_check_n_back(s + *i)))
		(*counter)++;
	*i += ft_get_op_len(s + *i);
	if (s[*i] && !ft_strchr(seps, s[*i]))
		(*counter)++;
}

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
			ft_handle_operator(&i, (char *)s, seps, &counter);
		else if (i > 0 && ft_strchr(seps, s[i]) && !ft_strchr(seps, s[i++ - 1]))
			counter++;
		else
			i++;
	}
	return (counter + (i > 0 && (!ft_strchr(seps, s[i - 1]))));
}

static size_t	ft_get_world_len(const char *s, char *seps)
{
	size_t	i;

	i = 0;
	if (!s || !seps)
		return (0);
	while (ft_isdigit(s[i]))
		i++;
	if (ft_get_op_len(s + i) > 0)
		i += ft_get_op_len(s + i);
	else
	{
		while (s[i] && (!ft_strchr(seps, s[i])) && !ft_get_op_len(s + i))
		{
			if (s[i] && ft_strchr("\'\"", s[i]))
				i += ft_quote_len(s + i);
			else if (s[i] == '(')
				i += ft_parenthesis_len(s + i);
			else
				i++;
		}
	}
	return (i);
}

static char	*ft_process_word(const char **s, char *seps)
{
	size_t	len;
	char	*word;

	len = ft_get_world_len(*s, seps);
	word = ft_calloc((len + 1), sizeof(char));
	if (!word)
		return (NULL);
	ft_memmove(word, *s, len);
	*s += len;
	return (word);
}

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
			return (ft_free_strarr_until(arr, i));
	}
	if (arr[0] != NULL)
		arr[word_count] = NULL;
	return (arr);
}

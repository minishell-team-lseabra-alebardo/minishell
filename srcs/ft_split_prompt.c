#include "../includes/libft.h"

static size_t	ft_quote_length(const char *s)
{
	size_t	len;
	char	quote;

	quote = s[0];
	len = 1;
	while (s[len] && quote != s[len])
		len++;
	return (len + 1);
}

static size_t	count_words(const char *s, char *seps)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i] && !ft_strchr("\'\"", s[i]) && ft_strchr(seps, s[i]))
		i++;
	while (s[i])
	{
		if (s[i] && ft_strchr("\'\"", s[i]))
			i += ft_quote_length(&s[i]);
		else
		{
			if (i > 0 && ft_strchr(seps, s[i]))
				counter++;
			i++;
		}
	}
	if (i > 0 && (!ft_strchr(seps, s[i - 1]) || ft_strchr("\'\"", s[i])))
		counter++;
	return (counter);
}

static char	**free_arr(char **arr, size_t position)
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

static char	*process_word(const char **s, char *seps)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	while ((*s)[i] && (!ft_strchr(seps, (*s)[i]) || ft_strchr("\'\"", (*s)[i])))
	{
		if ((*s)[i] && ft_strchr("\'\"", (*s)[i]))
			i += ft_quote_length(&(*s)[i]);
		else
			i++;
	}
	word = ft_calloc((i + 1), sizeof(char));
	if (!word)
		return (NULL);
	len = i;
	while (--i >= 0)
		word[i] = (*s)[i];
	(*s) += len;
	return (word);
}

char	**ft_split_prompt(const char *s, char *seps)
{
	size_t	word_count;
	size_t	i;
	char	**arr;

	word_count = count_words(s, seps);
	arr = ft_calloc((word_count + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < word_count)
	{
		while (ft_strchr(seps, *s) && !ft_strchr("\'\"", *s))
			s++;
		arr[i] = process_word(&s, seps);
		if (!arr[i])
			return (free_arr(arr, i));
	}
	if (arr[0] != NULL)
		arr[word_count] = NULL;
	return (arr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*s;
// 	char	*seps;
// 	char	**arr;
// 	int		i;

// 	s = "e'cho\" 	lalala\"\' arg1	arg2";
// 	seps = " 	";
// 	arr = ft_split_prompt(s, seps);
// 	i = 0;
// 	while (arr[i])
// 	{
// 		printf("p[%d]: %s\n", i, arr[i]);
// 		i++;
// 	}
// 	printf("p[%d]: %s\n", i, arr[i]);
// 	while (--i >= 0)
// 	{
// 		free(arr[i]);
// 	}
// 	free(arr);
// 	printf("og str: %s\n", s);
// 	return (0);
// }

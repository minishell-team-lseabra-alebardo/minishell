/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 04:25:58 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/08 16:37:43 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static char	*ft_create_new_line(char **names, char *wildtoken, int *wildmark)
{
	char	**split;
	char	*match;
	int		i;

	split = ft_split(wildtoken, '*');
	if (!split)
		return (0);
	match = (char *) ft_calloc((ft_count_names() * 257) + 1, 1);
	if (!match)
		return (NULL);
	i = 0;
	while (names[i])
	{
		if (ft_search_matches(split, names[i], wildmark))
		{
			ft_strlcat(match, names[i], (ft_count_names() * 257) + 1);
			ft_strlcat(match, " ", (ft_count_names() * 257) + 1);
		}
		i++;
	}
	ft_free_strarr(split);
	return (ft_check_match(match));
}

static char	*ft_copy_match(char *match, char *line, int wild_size, int *i)
{
	char	*new_line;
	int		match_len;
	int		j;

	match_len = ft_strlen(match);
	new_line = (char *) ft_calloc((ft_strlen(line) + match_len)
			- wild_size + 1, 1);
	if (!new_line)
		return (0);
	j = ft_copy_wildstart(new_line, line, *i);
	ft_copy_rest(new_line, match);
	j += wild_size;
	ft_copy_rest(new_line, &line[j]);
	*i += match_len;
	free(match);
	free(line);
	return (new_line);
}

static char	*ft_treat_wildcard(char **names, char *line, int *wildmark, int *i)
{
	char	*wildtoken;
	char	*match;
	int		j;

	j = 0;
	wildtoken = (char *) ft_calloc(wildmark[3] + 1, sizeof(char));
	if (!wildtoken)
		return (line);
	while (j < wildmark[3])
	{
		wildtoken[j] = line[*i + j];
		j++;
	}
	wildtoken = ft_search_wildquotes(wildtoken);
	match = ft_create_new_line(names, wildtoken, wildmark);
	free(wildtoken);
	if (!match)
	{
		while (line[*i])
			*i += 1;
		return (line);
	}
	return (ft_copy_match(match, line, wildmark[3], i));
}

static char	*ft_convert_wildcard(char **names, char *line)
{
	char	*new_line;
	int		wildmark[4];
	int		i;

	i = 0;
	new_line = ft_strdup(line);
	while (new_line[i])
	{
		while (new_line[i] && ft_is_whitespace(new_line[i]))
			i++;
		if (new_line[i] == '\'' || new_line[i] == '\"')
			i = ft_avoid_quotes(new_line, new_line[i], i + 1) + 1;
		else if (new_line[i] == '(')
			i = ft_avoid_parentheses(new_line, i) + 1;
		else if (new_line[i])
		{
			if (ft_search_wildcard(new_line, wildmark, i))
				new_line = ft_treat_wildcard(names, new_line, wildmark, &i);
			else
				i++;
		}
	}
	return (new_line);
}

char	*ft_wildcards(char *line)
{
	int		names_count;
	char	**names;
	char	*new_line;

	names_count = ft_count_names();
	if (names_count <= 0)
		return (line);
	names = ft_get_names(names_count);
	if (!names)
		return (line);
	new_line = ft_convert_wildcard(names, line);
	free(line);
	ft_free_strarr(names);
	return (new_line);
}

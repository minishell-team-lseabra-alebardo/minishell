#include <ft_minishell.h>

// int	ft_is_whitespace(char c)
// {
// 	if (!c || (c == ' ' || (c >= '\t' && c <= '\r')))
// 		return (1);
// 	return (0);
// }

// int	ft_avoid_quotes(char *arg, char quote, int i)
// {
// 	i++;
// 	while (arg[i] && arg[i] != quote)
// 		i++;
// 	return (i++);
// }

static int	ft_avoid_parentheses(char *line, int i)
{
	while (line[i] != ')')
		i++;
	return (i++);
}

static void	ft_move_wildchars(char *wildtoken)
{
	while (*wildtoken)
	{
		ft_memmove(wildtoken, wildtoken + 1, 1);
		wildtoken++;
	}
}

char	*ft_search_wildquotes(char *wildtoken)
{
	int		i;
	char	quote;

	i = 0;
	while (wildtoken[i])
	{
		if (wildtoken[i] == '\'' || wildtoken[i] == '\"')
		{
			quote = wildtoken[i];
			while (wildtoken[i] == quote)
				ft_move_wildchars(&wildtoken[i]);
		}
		else
			i++;
	}
	return (wildtoken);
}

int	ft_count_names(void)
{
	DIR				*dir;
	struct dirent	*cont;
	int				i;

	dir = opendir(".");
	if (!dir)
		return (-1);
	i = 0;
	while (1)
	{
		cont = readdir(dir);
		if (!cont)
			break ;
		if (ft_strncmp(cont->d_name, ".", 2)
			&& ft_strncmp(cont->d_name, "..", 3))
			i++;
	}
	closedir(dir);
	return (i);
}

char	**ft_get_names(int names_count)
{
	int				i;
	char			**names;
	DIR				*dir;
	struct dirent	*cont;

	names = (char **) ft_calloc(names_count + 1, sizeof(char *));
	if (!names)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	i = 0;
	while (1)
	{
		cont = readdir(dir);
		if (!cont)
			break;
		if (ft_strncmp(cont->d_name, ".", 2)
			&& ft_strncmp(cont->d_name, "..", 3))
			names[i] = strdup(cont->d_name);
	}
	closedir(dir);
	return (names);
}

int	ft_search_wildcard(char *line, int *wildmark, int start)
{
	int		i;

	i = start + 1;
	wildmark[0] = 0;
	wildmark[1] = 0;
	wildmark[2] = 0;
	wildmark[3] = 0;
	if (line[start] == '*')
		wildmark[0] = 1;
	while (!ft_is_whitespace(line[i]))
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = ft_avoid_quotes(line, line[i], i);
		if (line[i] == '*')
			wildmark[1] = 1;
		i++;
	}
	wildmark[3] = i - start;
	if (line[i - 1] == '*')
		wildmark[2] = 1;
	if (wildmark[0] || wildmark[1] || wildmark[2])
		return (1);
	return (0);
}

char	*ft_match_ends(char **split, char *name, int *wildmark)
{
	char	*temp;
	int		i;
	int		j;

	temp = name;
	i = 0;
	j = 0;
	if (!wildmark[2])
	{
		while (split[i + 1])
			i++;
		while (temp[j])
			j++;
		while (temp[j - 1] != '*')
			j--;
		if (ft_strncmp(split[i], &temp[j], ft_strlen(split[i])))
			return (0);
	}
	if (!wildmark[0] && ft_strncmp(split[0], temp, ft_strlen(split[i])))
		return (0);
	else if (!wildmark[0] && !ft_strncmp(split[0], temp, ft_strlen(split[i])))
		return (&temp[ft_strlen(split[0])]);
	return (temp);
}

int	ft_search_matches(char **split, char *name, int *wildmark)
{
	int		i;
	char	*temp;

	i = 0;
	temp = name;
	if (!split[0])
		return (1);
	if (!wildmark[0] || !wildmark[2])
	{
		temp = ft_match_ends(split, name, wildmark);
		i++;
	}
	if (!temp)
		return (0);
	while (wildmark[1] && split[i] && *temp)
	{
		if (!ft_strncmp(split[i], temp, ft_strlen(split[i])))
		{
			i++;
			temp += ft_strlen(split[i]);
		}
		else
			temp++;
		if (!wildmark[2] && !split[i + 1])
			break;
	}
	if (!wildmark[2] && !split[i + 1])
		return (1);
	else if (!split[i])
		return (1);
	return (0);
}

char	*ft_create_new_line(char **names, char *wildtoken, int *wildmark)
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
	// FIX THIS new_line[i - 1] = 0;
	if (!match[0])
		return (0);
	return (match);
}

char	*ft_copy_match(char *match, char *line, int wild_size, int *i)
{
	char	*new_line;
	int		match_len;
	int		j;

	match_len = ft_strlen(match);
	new_line = (char *) ft_calloc((ft_strlen(line) + match_len)
		- wild_size + 1, 1);
	if (!new_line)
		return (0);
	j = ft_copy_start(new_line, line, *i);
	ft_copy_rest(new_line, match);
	j += wild_size;
	ft_copy_rest(new_line, &line[j]);
	*i += match_len - 1;
	return (new_line);
}

char	*ft_treat_wildcard(char **names, char *line, int *wildmark, int *start)
{
	char	*wildtoken;
	char	*match;
	int		i;

	i = 0;
	wildtoken = (char *) ft_calloc(wildmark[3] + 1, sizeof(char));
	if (!wildtoken)
		return (line);
	while (i < wildmark[3])
	{
		wildtoken[i] = line[*start + i];
		i++;
	}
	wildtoken = ft_search_wildquotes(wildtoken);
	match = ft_create_new_line(names, wildtoken, wildmark);
	if (!match)
		return (line);
	return (ft_copy_match(match, line, wildmark[3], start));
}

char	*ft_convert_wildcard(char **names, char *line)
{
	char	*new_line;
	int		wildmark[4];
	int		i;

	i = 0;
	new_line = ft_strdup(line);
	while(line[i])
	{
		while (ft_is_whitespace(line[i]))
			i++;
		if (line[i] == '\'' || line[i] == '\"')
			i = ft_avoid_quotes(line, line[i], i);
		else if (line[i] == '(')
			i = ft_avoid_parentheses(line, i);
		else if (line[i])
		{
			if (ft_search_wildcard(line, wildmark, i))
				new_line = ft_treat_wildcard(names, line, wildmark, &i);
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
	if (names_count < 0)
		return (line);
	if (!names_count)
		return (line);
	names = ft_get_names(names_count);
	if (!names)
		return (line);
	new_line = ft_convert_wildcard(names, line);
	free(line);
	return (new_line);
}

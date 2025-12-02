#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

int	ft_is_whitespace(char c)
{
	if (!c || (c == ' ' || (c >= '\t' && c <= '\r')))
		return (1);
	return (0);
}

int	ft_avoid_quotes(char *arg, char quote, int i)
{
	i++;
	while (arg[i] && arg[i] != quote)
		i++;
	return (i++);
}

int	ft_avoid_parentheses(char *line, int i)
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
		if (strncmp(cont->d_name, ".", 2) && strncmp(cont->d_name, "..", 3))
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

	names = (char **) calloc(names_count + 1, sizeof(char *));
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
		if (strncmp(cont->d_name, ".", 2) && strncmp(cont->d_name, "..", 3))
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

int	ft_search_matches(char **split, char *name, int *wildmark)
{
	int		i;
	char	*temp;

	i = 0;
	temp = name;
	if (!wildmark[0] && strncmp(split[i], temp, strlen(split[i])))
		return (0);
	else if (!wildmark[0] && !strncmp(split[i], temp, strlen(split[i])))
	{
		i++;
		temp = &temp[strlen(split[i])];
	}
	while (wildmark[1] && split[i])
	{

	}
	//CONTINUE HERE
}

char	*ft_create_new_line(char **names, char *wildtoken, int *wildmark)
{
	char	**split;
	char	*new_line;
	int		i;

	split = ft_split(wildtoken, '*');
	if (!split)
		return (0);
	new_line = (char *) calloc((ft_count_names() * 256) + 1, 1);
	if (!new_line)
		return (NULL);
	i = 0;
	while (names[i])
	{
		if (ft_search_matches(split, names[i], wildmark))
		{
			ft_strlcat(new_line, names[i], (ft_count_names() * 256) + 1);
			ft_strlcat(new_line, " ", (ft_count_names() * 256) + 1);
		}
		i++;
	}
	new_line[i - 1] = 0;
	if (!new_line[0])
		return (0);
	return (new_line);
}

char	*ft_treat_wildcard(char **names, char *line, int *wildmark, int start)
{
	char	*wildtoken;
	char	*new_line;
	char	i;

	i = 0;
	wildtoken = (char *) calloc(wildmark[3] + 1, sizeof(char));
	if (!wildtoken)
		return (line);
	while (i < wildmark[3])
	{
		wildtoken[i] = line[start + i];
		i++;
	}
	wildtoken = ft_search_wildquotes(wildtoken);
	new_line = ft_create_new_line(names, wildtoken, wildmark);
	if (!new_line)
		return (line);
	//CONTINUE HERE
}

char	*ft_convert_wildcard(char **names, char *line)
{
	char	*new_line;
	int		wildmark[4];
	int		i;

	i = 0;
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
				new_line = ft_treat_wildcard(names, line, wildmark, i);
			else
				while (!ft_is_whitespace(line[i]))
					i++;
		}
	}
}

char	*ft_wildcards(char *line)
{
	int		names_count;
	char	**names;
	char	*new_line;

	names_count = ft_count_names();
	if (names_count < 0)
		return (-1);
	if (!names_count)
		return (line);
	names = ft_get_names(names_count);
	if (!names)
		return (-1);
	new_line = ft_convert_wildcard(names, line);
	free(line);
	return (new_line);
}

int	main(void)
{
	DIR				*directory;
	struct dirent	*contents;

	directory = opendir("/home/magusk/test_codes");
	if (!directory)
	{
		puts("Directory not open");
		return (-1);
	}
	contents = readdir(directory);
	while (contents)
	{
		if (strncmp(contents->d_name, ".", 2) && strncmp(contents->d_name, "..", 3))
			printf("%s\n", contents->d_name);
		contents = readdir(directory);
	}
	closedir(directory);
}
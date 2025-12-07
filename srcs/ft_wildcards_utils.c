/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 04:23:24 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/07 04:28:29 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	ft_avoid_parentheses(char *line, int i)
{
	while (line[i] != ')')
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = ft_avoid_quotes(line, line[i], i + 1);
		i++;
	}
	return (i);
}

void	ft_move_wildchars(char *wildtoken)
{
	while (*wildtoken)
	{
		ft_memmove(wildtoken, wildtoken + 1, 1);
		wildtoken++;
	}
}

int	ft_copy_wildstart(char *new_arg, char *arg, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		new_arg[j] = arg[j];
		j++;
	}
	return (j);
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
			i = ft_avoid_quotes(line, line[i], i + 1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match_wildcards.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 04:20:53 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/07 04:22:24 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

char	*ft_check_match(char *match)
{
	int		i;

	if (!match[0])
	{
		free(match);
		return (0);
	}
	else
	{
		i = 0;
		while (match[i])
			i++;
		match[i - 1] = 0;
	}
	return (match);
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
		if (ft_strncmp(split[i], &temp[j - ft_strlen(split[i])],
				ft_strlen(split[i])))
			return (0);
	}
	if (!wildmark[0] && ft_strncmp(split[0], temp, ft_strlen(split[i])))
		return (0);
	else if (!wildmark[0] && !ft_strncmp(split[0], temp, ft_strlen(split[i])))
		return (&temp[ft_strlen(split[0])]);
	return (temp);
}

void	ft_match_middle(char **split, char *temp, int *wildmark, int *i)
{
	while (wildmark[1] && split[*i] && *temp)
	{
		if (!ft_strncmp(split[*i], temp, ft_strlen(split[*i])))
		{
			temp += ft_strlen(split[*i]);
			*i += 1;
		}
		else
			temp++;
		if (!wildmark[2] && !split[*(i) + 1])
			break ;
	}
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
		if (!wildmark[0])
			i++;
	}
	if (!temp)
		return (0);
	ft_match_middle(split, temp, wildmark, &i);
	if (!wildmark[2] && !split[i + 1])
		return (1);
	else if (!split[i])
		return (1);
	return (0);
}

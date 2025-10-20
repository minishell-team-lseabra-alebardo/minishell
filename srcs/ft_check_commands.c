/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:29:12 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/20 15:10:06 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static char	*ft_skip_whitespaces(char *line)
{
	char	*temp;

	temp = line;
	while (*temp == WS_SPACE || (*temp >= WS_HTAB && *temp <= WS_RETURN))
		temp++;
	return (temp);
}

static char	*ft_skip_quotes(char *line, char c)
{
	char	*temp;

	temp = line;
	temp++;
	while (*temp && *temp != c)
		temp++;
	return (temp);
}

int	ft_check_commands(char *line)
{
	char	*temp;

	temp = ft_skip_whitespaces(line);
	if (!*temp || (*temp == '&' && *(temp + 1) == '&') || *temp == '|')
		return (-1);
	while (*temp)
	{
		if (*temp == '&')
			temp++;
		if (*temp == '&' || *temp == '|')
		{
			temp++;
			if (*temp == '|')
				temp++;
			return (ft_check_commands(temp));
		}
		if (*temp == '\"' || *temp == '\'')
			temp = ft_skip_quotes(temp, *temp);
		if (*temp)
			temp++;
	}
	return (0);
}

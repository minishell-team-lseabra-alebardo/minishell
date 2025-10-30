/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skips.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:44:28 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/28 16:00:36 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

char	*ft_skip_whitespaces(char *line)
{
	char	*temp;

	temp = line;
	while (*temp == WS_SPACE || (*temp >= WS_HTAB && *temp <= WS_RETURN))
		temp++;
	return (temp);
}

char	*ft_skip_quotes(char *line, char c)
{
	char	*temp;

	temp = line;
	temp++;
	while (*temp && *temp != c)
		temp++;
	return (temp);
}

char	*ft_skip_open_parentheses(char *line)
{
	char	*temp;

	temp = ft_skip_whitespaces(line);
	while (*temp == '(')
	{
		temp++;
		temp = ft_skip_whitespaces(temp);
	}
	return (temp);
}

char	*ft_skip_and(char *line)
{
	char	*temp;

	temp = line;
	temp += 2;
	temp = ft_skip_whitespaces(temp);
	if (*temp == '(')
		temp++;
	return (temp);
}

char	*ft_skip_pipe_or(char *line)
{
	char	*temp;

	temp = line;
	temp++;
	if (*temp == '|')
		temp++;
	temp = ft_skip_whitespaces(temp);
	if (*temp == '(')
		temp++;
	return (temp);
}

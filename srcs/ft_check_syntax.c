/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:29:12 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/27 21:31:51 by alebarbo         ###   ########.fr       */
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

static char	*ft_skip_open_parentheses(char *line)
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

static char	*ft_skip_and(char *line)
{
	char	*temp;

	temp = line;
	temp += 2;
	temp = ft_skip_whitespaces(temp);
	if (*temp == '(')
		temp++;
	return (temp);
}

static char	*ft_skip_pipe_or(char *line)
{
	char	*temp;

	temp = line;
	temp++;
	if (*temp == '|')
		temp++;
	temp = ft_skip_whitespaces(temp);
	if (temp == '(')
		temp++;
	return (temp);
}

int	ft_check_operators(char *line)
{
	char	*temp;

	temp = ft_skip_whitespaces(line);
	if (!*temp || (*temp == '&' && *(temp + 1) == '&')
		|| *temp == '|' || *temp == ')')
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
			return (ft_check_operators(temp));
		}
		if (*temp == '\"' || *temp == '\'')
			temp = ft_skip_quotes(temp, *temp);
		if (*temp)
			temp++;
	}
	return (0);
}

int	ft_check_empty_parentheses(char *line)
{
	char	*temp;

	temp = ft_skip_whitespaces(line);
	while (*temp)
	{
		if (*temp == '(')
		{
			temp = ft_skip_whitespaces(temp);
			if (*temp == ')')
				return (-1);
		}
		if (*temp == '\'' || *temp == '\"')
			temp = ft_skip_quotes(temp, *temp);
		temp++;
	}
	return (0);
}

int	ft_check_invalid_parentheses(char *line)
{
	char	*temp;

	temp = ft_skip_whitespaces(line);
	while (*temp)
	{
		temp = ft_skip_open_parentheses(temp);
		if (*temp == '\'' || *temp == '\"')
			temp = ft_skip_quotes(temp, *temp);
		if (*temp == '&' && *(temp + 1) == '&')
			temp = ft_skip_and(temp);
		else if (*temp == '|')
			temp = ft_skip_pipe_or(temp);
		else if (*temp == '(')
			return (-1);
		else
			temp++;
	}
	return (0);
}

int	ft_check_syntax(char *line)
{
	if (ft_check_unclosed(line) < 0
		|| ft_check_operators(line) < 0
		|| ft_check_empty_parentheses(line) < 0
		|| ft_check_invalid_parentheses(line) < 0)
		return (-1);
	return (0);
}

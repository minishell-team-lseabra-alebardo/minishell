/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:48:27 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/22 10:27:20 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static char	*ft_check_single(char *line)
{
	char	*temp;

	temp = line;
	temp++;
	while (temp && *temp)
	{
		if (*temp == '\'')
			return (temp + 1);
		temp++;
	}
	return (0);
}

static char	*ft_check_double(char *line)
{
	char	*temp;

	temp = line;
	temp++;
	while (temp && *temp)
	{
		if (*temp == '\"')
			return (temp + 1);
		temp++;
	}
	return (0);
}

static char	*ft_check_parentheses(char *line)
{
	char	*temp;

	temp = line;
	temp++;
	while (temp && *temp)
	{
		if (*temp == ')')
			return (temp + 1);
		else if (*temp == '(')
			temp = ft_check_parentheses(temp);
		else if (*temp == '\'')
			temp = ft_check_single(temp);
		else if (*temp == '\"')
			temp = ft_check_double(temp);
		else if (temp && *temp)
			temp++;
	}
	return (0);
}

int	ft_check_unclosed(char *line)
{
	char	*temp;

	temp = line;
	while (temp && *temp)
	{
		if (*temp == '(')
			temp = ft_check_parentheses(temp);
		else if (*temp == ')')
			return (-1);
		else if (*temp == '\'')
			temp = ft_check_single(temp);
		else if (*temp == '\"')
			temp = ft_check_double(temp);
		else if (temp && *temp)
			temp++;
	}
	if (!temp)
		return (-1);
	return (0);
}

int	ft_check_empty_line(char *line)
{
	char	*temp;

	temp = ft_skip_whitespaces(line);
	if (!*temp)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:51 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/15 15:08:01 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

char	*ft_check_parentheses(char *line)
{
	while (*line)
	{
		if (*line == ')')
			return (line);
		else if (*line == '\'')
			line = ft_check_single(line);
		else if (*line == '\"')
			line = ft_check_double(line);
		line++;
	}
	//RETURN ERROR HERE
}

char	*ft_check_single(char *line)
{
	while (*line)
	{
		if (*line == '\'')
			return (line);
		line++;
	}
	//RETURN ERROR HERE
}

char	*ft_check_double(char *line)
{
	while (*line)
	{
		if (*line == '\"')
			return (line);
		line++;
	}
	//RETURN ERROR HERE
}

void	ft_parser(char *line)
{
	//CHECK FOR UNCLOSED QUOTES/PARENTHESES
	/*
	while (*line)
	{
		if (*line == '(')
			ft_check_parentheses(line);
		else if (*line == '\'')
			ft_check_single(line);
		else if (*line == '\"')
			ft_check_double(line);
		line++;
	}
	*/
	
}
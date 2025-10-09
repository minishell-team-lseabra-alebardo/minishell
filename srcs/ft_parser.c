/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 01:52:15 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/07 02:53:59 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.c>

//CHECK WHITESPACES BEFORE FIRST ARGUMENT
//CHECK FOR OPENING QUOTES (SINGLE AND DOUBLE)
//CHECK FOR THE CLOSING QUOTES
//IF INSIDE QUOTES, CHECK FOR WHITESPACES AGAIN
//CHECK FOR OPERATORS
//CHECK FOR VARIABLES
//CHECK FOR ARGUMENTS
//IF ARGUMENT IS INSIDE QUOTES, CHECK FOR VARIABLES
//FIND A WAY TO ASSOCIATE INFILE/OUTFILE TO ITS RESPECTIVE OPERATORS
//IMPLEMENT HERE_DOC

static char	*ft_check_whitespaces(char *line)
{
	while (*line == " " || (*line >= "\b" && *line <= "\r"))
		line++;
	return (line);
}

void	ft_parser(char *line)
{
	char	*temp;

	line = ft_check_whitespaces(line);
	if (*line == SINGLE_QUOTE)
	{
		temp = line;
		temp++;
		while (*temp)
		{
			if (*temp == SINGLE_QUOTE)
				return (temp);
			temp++;
		}
		return (0);
	}
}
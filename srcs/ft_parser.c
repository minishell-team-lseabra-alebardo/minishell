/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:51 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/16 22:41:08 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_parser(char *line)
{
	char	**broken_line;
	int		i;

	if (ft_check_unclosed(line) < 0)
	{
		write(2, "Syntax error\n", 13);
		return ;
	}
	broken_line = ft_split_prompt(line, WS_POSIX);
	i = 0;
	while (broken_line[i])
	{
		printf("%s\n", broken_line[i]);
		free(broken_line[i]);
		i++;
	}
	free(broken_line);
}

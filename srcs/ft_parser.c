/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:51 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/20 00:23:22 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_temp_split_test(char *line)
{
	char	**split_line;
	int		i;

	split_line = ft_split_prompt(line, WS_POSIX);
	i = 0;
	while (split_line[i])
	{
		printf("%s\n", split_line[i]);
		free(split_line[i]);
		i++;
	}
	free(split_line);
}

void	ft_parser(char *line)
{
	if (ft_check_unclosed(line) < 0 || ft_check_commands(line) < 0)
	{
		write(2, ERR_SYNTAX, 13);
		return ;
	}
	ft_temp_split_test(line);
}

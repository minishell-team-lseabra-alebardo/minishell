/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:08:09 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/01 03:19:59 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_read_line(void)
{
	char	*line;

	while (1)
	{
		line = readline("Prompt: ");
		if (!line)
			break ;
		if (line && *line)
		{
			add_history(line);
			if (!strcmp(line, "exit"))
			{
				free(line);
				break ;
			}
			ft_built_ins(line);
		}
		free(line);
	}
}

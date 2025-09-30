/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:46:59 by alebarbo          #+#    #+#             */
/*   Updated: 2025/09/30 16:24:10 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_minishell.h"

int	main(void)
{
	char	*line;

	ft_listener();
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
	printf("exit\n");
	exit(0);
}

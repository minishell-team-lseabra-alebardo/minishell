/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:46:59 by alebarbo          #+#    #+#             */
/*   Updated: 2025/09/30 00:30:42 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	char	*line;

	while(1)
	{
		line = readline("Prompt: ");
		if (line)
		{
			if (*line)
				add_history(line);
			if (!strcmp(line, "clear"))
				rl_clear_history();
			if (!strcmp(line, "exit"))
			{
				free(line);
				exit(0);
			}
			free(line);
		}
	}
}
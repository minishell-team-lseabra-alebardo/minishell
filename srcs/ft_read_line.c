/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:08:09 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/01 23:41:37 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_free_prompt_line(char *prompt, char *line)
{
	free(prompt);
	free(line);
}

static void	ft_exiting(char *prompt, char *line)
{
	ft_free_prompt_line(prompt, line);
	printf("exit\n");
	exit(0);
}

void	ft_read_line(void)
{
	char	*prompt;
	char	*line;

	while (1)
	{
		prompt = ft_get_ps1();
		line = readline(prompt);
		if (!line)
			ft_exiting(prompt, line);
		if (line && *line)
		{
			add_history(line);
			if (!ft_strncmp(line, "exit", 5))
				ft_exiting(prompt, line);
		}
		ft_free_prompt_line(prompt, line);
	}
}

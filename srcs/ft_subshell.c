/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:46:46 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/14 23:02:09 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_remove_parentheses(char *line)
{
	while (*line)
	{
		ft_memmove(line, line + 1, 1);
		line++;
	}
	if (*(line - 1) == ')')
		*(line - 1) = 0;
}

void	ft_subshell(t_data *dt, char **argv)
{
	char	*line;

	puts("This is subshell!");
	line = ft_strdup(argv[1]);
	if (line[0] == '(')
		ft_remove_parentheses(line);
	ft_args_treatment(&line, dt->ms_envp, 0);
	dt->split_line = ft_split_prompt(line, WS_POSIX);
	ft_parser(dt);
	ft_exec_line(dt);
	ft_exiting(0, line, dt);
}
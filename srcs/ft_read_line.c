/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:08:09 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/14 16:08:36 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_free_prompt_line(char *prompt, char *line)
{
	if (prompt)
		free(prompt);
	if (line)
		free(line);
}

static void	ft_free_ms_envp(char **ms_envp)
{
	int		i;

	i = 0;
	while (ms_envp[i])
	{
		free(ms_envp[i]);
		i++;
	}
	free(ms_envp);
}

static void	ft_exiting(char *prompt, char *line, t_data *dt)
{
	ft_free_prompt_line(prompt, line);
	ft_free_ms_envp(dt->ms_envp);
	free(dt);
	printf("exit\n");
	exit(0);
}

void	ft_read_line(t_data *dt)
{
	char	*prompt;
	char	*line;

	while (1)
	{
		prompt = ft_get_ps1();
		line = readline(prompt);
		if (!line)
			ft_exiting(prompt, line, dt);
		if (line && *line)
		{
			add_history(line);
			if (ft_check_syntax(line) < 0)
				write(2, ERR_SYNTAX, 13);
			else
			{
				ft_args_treatment(&line, dt->ms_envp, 0);
				dt->split_line = ft_split_prompt(line, WS_POSIX);
				ft_parser(dt);
				ft_exec_line(dt);
			}
		}
		ft_free_prompt_line(prompt, line);
	}
}

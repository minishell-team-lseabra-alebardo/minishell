/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:25:09 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/14 23:03:50 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_close_error(t_data *dt)
{
	perror(strerror(errno));
	if (dt)
	{
		if (dt->ms_envp)
			ft_free_ms_envp(dt->ms_envp);
		free(dt);
	}
	exit(EXIT_FAILURE);
}

void	ft_free_prompt_line(char *prompt, char *line)
{
	if (prompt)
		free(prompt);
	if (line)
		free(line);
}

void	ft_free_ms_envp(char **ms_envp)
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

void	ft_exiting(char *prompt, char *line, t_data *dt)
{
	ft_free_prompt_line(prompt, line);
	ft_free_ms_envp(dt->ms_envp);
	free(dt);
	printf("exit\n");
	exit(0);
}

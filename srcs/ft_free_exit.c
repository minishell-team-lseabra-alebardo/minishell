/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:25:09 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/19 15:30:03 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_close_error(t_data *dt)
{
	perror(strerror(errno));
	if (dt)
	{
		if (dt->ms_envp)
			ft_free_strarr(dt->ms_envp);
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

void	ft_free_strarr(char **strarr)
{
	int	i;

	if (!strarr)
		return ;
	i = 0;
	while (strarr[i])
	{
		free(strarr[i]);
		i++;
	}
	free(strarr);
}

int	ft_exit(t_data *dt)
{
	ft_close_unused_fds(dt->cmd_ll);
	ft_cleanup_line(dt);
	ft_free_strarr(dt->ms_envp);
	ft_free_prompt_line(dt->prompt, dt->line);
	free(dt);
	printf("exit\n");
	exit(0);
}

int	ft_exit_subshell(t_data *dt)
{
	ft_close_unused_fds(dt->cmd_ll);
	ft_cleanup_line(dt);
	ft_free_strarr(dt->ms_envp);
	ft_free_prompt_line(dt->prompt, dt->line);
	free(dt);
	exit(0);
}

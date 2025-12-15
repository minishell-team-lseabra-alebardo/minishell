/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:25:09 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/15 17:22:36 by alebarbo         ###   ########.fr       */
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

void	ft_free_prompt_line(t_data *dt)
{
	if (dt->prompt)
	{
		free(dt->prompt);
		dt->prompt = NULL;
	}
	if (dt->line)
	{
		free(dt->line);
		dt->line = NULL;
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:25:09 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/09 03:51:13 by alebarbo         ###   ########.fr       */
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

int	ft_exit(t_data *dt, t_cmd *cmd)
{
	int		pexit;

	pexit = dt->pexit;
	ft_close_unused_fds(dt->cmd_ll);
	ft_free_strarr(dt->ms_envp);
	ft_free_prompt_line(dt);
	ft_cleanup_line(dt);
	free(dt);
	if (pexit && (!cmd || (cmd && !ft_is_in_pipeline(cmd))))
		printf("exit\n");
	if (ft_get_status(0, false) == EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

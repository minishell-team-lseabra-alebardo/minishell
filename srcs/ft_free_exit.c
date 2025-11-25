/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:25:09 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/24 19:42:28 by alebarbo         ###   ########.fr       */
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

int	ft_exit(t_data *dt, t_cmd *cmd)
{
	int		lst_stat;

	lst_stat = dt->lst_stat;
	ft_close_unused_fds(dt->cmd_ll);
	ft_free_strarr(dt->ms_envp);
	ft_free_prompt_line(dt->prompt, dt->line);
	if (dt->pexit && (!cmd || (cmd && !ft_is_in_pipeline(cmd))))
		printf("exit\n");
	ft_cleanup_line(dt);
	free(dt);
	if (lst_stat == EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

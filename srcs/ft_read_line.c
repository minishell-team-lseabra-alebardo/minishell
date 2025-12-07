/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:08:09 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/07 01:19:52 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_read_line(t_data *dt)
{
	while (1)
	{
		dt->prompt = ft_get_ps1(dt->ms_envp);
		dt->line = readline(dt->prompt);
		if (!dt->line)
			ft_exit(dt, NULL);
		if (dt->line && *dt->line)
		{
			add_history(dt->line);
			if (ft_check_syntax(dt->line) < 0)
				write(2, ERR_SYNTAX, 13);
			else
			{
				ft_args_treatment(&dt->line, dt->ms_envp, 0);
				dt->split_line = ft_split_prompt(dt->line, WS_POSIX);
				ft_parser(dt);
				ft_exec_line(dt);
			}
		}
		ft_free_prompt_line(dt->prompt, dt->line);
	}
}

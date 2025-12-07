/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:08:09 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/06 22:26:10 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_treat_line(t_data *dt)
{
	if (!dt->line)
		ft_exit(dt, NULL);
	if (dt->line && *dt->line)
	{
		if (ft_strncmp(dt->line, dt->prev_line, ft_strlen(dt->line)))
		{
			ft_free_prev_line(dt);
			add_history(dt->line);
		}
		if (ft_check_syntax(dt->line) < 0)
			write(2, ERR_SYNTAX, 13);
		else
		{
			ft_args_treatment(&dt->line, dt, 0);
			dt->split_line = ft_split_prompt(dt->line, WS_POSIX);
			ft_parser(dt);
			ft_exec_line(dt);
		}
	}
	dt->last_status = ft_get_status(0, false);
}

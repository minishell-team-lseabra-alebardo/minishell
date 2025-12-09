/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:08:09 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/09 03:41:40 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static char	*ft_prev_line(char *line)
{
	static char	prev_line[9999];
	int		i;

	i = 0;
	if (line)
	{
		ft_bzero(prev_line, 9999);
		while (line && line[i])
		{
			prev_line[i] = line[i];
			i++;
		}
	}
	return (prev_line);
}

void	ft_treat_line(t_data *dt)
{
	if (!dt->line)
		ft_exit(dt, NULL);
	if (dt->line && *dt->line)
	{
		if (ft_strncmp(dt->line, ft_prev_line(0), ft_strlen(dt->line)))
		{
			add_history(dt->line);
			ft_prev_line(dt->line);
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
}

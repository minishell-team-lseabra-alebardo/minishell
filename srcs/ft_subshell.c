/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:46:46 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/15 18:33:07 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_remove_parentheses(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		ft_memmove(&line[i], &line[i + 1], 1);
		i++;
	}
	i = 0;
	while (line[i])
		i++;
	line[i - 1] = 0;
}

int	ft_subshell(char **args, char **envp)
{
	t_data	*dt;

	dt = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!dt)
		ft_close_error(0);
	dt->subshell = 1;
	dt->ms_envp = ft_strarr_dup(envp);
	if (!dt->ms_envp)
		ft_close_error(dt);
	dt->last_status = ft_get_status(0, false);
	dt->line = ft_strdup(args[0]);
	if (dt->line[0] == '(')
		ft_remove_parentheses(dt->line);
	ft_args_treatment(&dt->line, dt, 0);
	dt->split_line = ft_split_prompt(dt->line, WS_POSIX);
	ft_parser(dt);
	ft_exec_line(dt);
	return (ft_cleanup_subshell(dt));
}

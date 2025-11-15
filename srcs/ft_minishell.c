/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:46:59 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/15 20:43:58 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*dt;

	if (ft_listener() < 0)
		ft_close_error(0);
	dt = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!dt)
		return (EXIT_FAILURE);
	dt->ms_envp = ft_strarr_dup(envp);
	if (!dt->ms_envp)
		return (EXIT_FAILURE);
	dt->lst_stat = 0;
	dt->cmd_ll = NULL;
	if (argc > 1 && !ft_strncmp("minishell", argv[0], 10)
		&& argv[1][0] == '(')
		ft_subshell(dt, argv);
	if (ft_ms_path(dt) < 0)
		ft_close_error(dt);
	ft_read_line(dt);
}

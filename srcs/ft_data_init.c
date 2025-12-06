/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:27:46 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/06 22:29:02 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

t_data	*ft_data_init(char **envp)
{
	t_data	*dt;

	dt = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!dt)
		ft_close_error(0);
	dt->ms_envp = ft_strarr_dup(envp);
	if (!dt->ms_envp)
		ft_close_error(dt);
	dt->last_status = 0;
	dt->prompt = NULL;
	dt->line = NULL;
	dt->prev_line = ft_strdup("");
	dt->cmd_ll = NULL;
	dt->pexit = 1;
	if (ft_ms_path(dt) < 0 || ft_shlvl(dt) < 0)
		ft_close_error(dt);
	return (dt);
}

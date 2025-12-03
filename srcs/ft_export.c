/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:31:20 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/03 17:22:00 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static size_t	ft_get_envp_len(char **ms_envp)
{
	size_t	i;

	if (!ms_envp)
		return (0);
	i = 0;
	while (ms_envp[i])
		i++;
	return (i);
}

int	ft_export(t_cmd *cmd, t_data *dt)
{
	size_t	envp_len;

	envp_len = ft_get_envp_len(dt->ms_envp);
	if (!cmd || !cmd->args || !dt->ms_envp)
		return (EXIT_FAILURE);
	else if (cmd->args[1] && !ft_is_in_pipeline(cmd))
		return (ft_export_vars(cmd->args + 1, dt, envp_len));
	else if (cmd->args[0])
		return (ft_print_ordered_exp(dt->ms_envp));
	return (EXIT_SUCCESS);
}

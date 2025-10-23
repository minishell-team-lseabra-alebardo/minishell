/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:46:59 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/27 09:44:53 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*dt;

	(void) argc;
	(void) argv;
	if (ft_listener() < 0)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	dt = ft_calloc(1, sizeof(t_data *));
	if (!dt)
		return (EXIT_FAILURE);
	dt->ms_envp = ft_strarr_dup(envp);
	if (!dt->ms_envp)
		return (EXIT_FAILURE);
	dt->lst_stat = 0;
	dt->list = NULL;
	ft_read_line(dt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:18:51 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/16 18:19:14 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

unsigned char	ft_get_status(unsigned char last_status, bool flag)
{
	static unsigned char	status;

	if (flag)
		status = last_status;
	return (status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*dt;

	(void) argc;
	(void) argv;
	ft_sigquit_listener();
	dt = ft_data_init(envp);
	while (1)
	{
		dt->last_status = ft_get_status(0, false);
		ft_get_status(0, true);
		ft_sigint_readline_listener();
		dt->prompt = ft_get_ps1(dt->ms_envp);
		dt->line = readline(dt->prompt);
		ft_sigint_listener();
		if (ft_get_status(0, false) == 130)
		{
			dt->last_status = ft_get_status(0, false);
			ft_get_status(0, true);
		}
		ft_treat_line(dt);
		ft_free_prompt_line(dt);
	}
}

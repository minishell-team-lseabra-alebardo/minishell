/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:46:59 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/06 19:38:38 by alebarbo         ###   ########.fr       */
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

	dt = 0;
	if (ft_listener() < 0)
		ft_close_error(0);
	if (argc > 1 && !ft_strncmp("minishell", argv[0], 10) && argv[1][0] == '(')
		return (ft_subshell(argv, envp));
	dt = ft_data_init(envp);
	while (1)
	{
		dt->prompt = ft_get_ps1(dt->ms_envp);
		dt->line = readline(dt->prompt);
		ft_treat_line(dt);
		ft_free_prompt_line(dt);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:46:59 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/06 00:15:29 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*dt;

	dt = 0;
	if (ft_listener() < 0)
		ft_close_error(0);
	if (argc > 1 && !ft_strncmp("minishell", argv[0], 10) && argv[1][0] == '(')
		return (ft_subshell(argv, envp));
	while (1)
	{
		ft_free_data(dt);
		dt = ft_data_init(envp);
		ft_treat_line(dt);
	}
}
